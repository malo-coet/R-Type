#include "ServerNetworkManager.hpp"
#include "systems/NetworkReceiveSystem.hpp"
#include "systems/NetworkSendSystem.hpp"
#include "ecs.hpp"
#include "components/typeComponent.hpp"
#include "systems/SpawnFromConfigSystem.hpp"
#include "components/component.hpp"
#include "components/networksComponents.hpp"
#include "Protocol.hpp"
#include "CommonLib/factory/EntityFactory.hpp"
#include "CommonLib/entitycomponents.hpp"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

ServerNetworkManager::ServerNetworkManager()
    : host_(nullptr)
{
    getFilter().require<NetworkComponent>();
}

ServerNetworkManager::~ServerNetworkManager() {
    if (host_) {
        enet_host_destroy(host_);
    }
    enet_deinitialize();
}

bool ServerNetworkManager::initializeServer(uint16_t port) {
    if (enet_initialize() != 0) {
        std::cerr << "Failed to initialize ENet.\n";
        return false;

    }
    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = port;
    host_ = enet_host_create(&address, 32, 2, 0, 0);
    if (!host_) {
        std::cerr << "Failed to create ENet server.\n";
        return false;
    }
    return true;
}

void ServerNetworkManager::onStart() {
    uint16_t port = 1234;
    if (!initializeServer(port)) {
        throw std::runtime_error("Failed to start server on port " + std::to_string(port));
    }
    std::cout << "Server running on port " << port << "...\n";
}

void ServerNetworkManager::handleNewConnection(ENetPeer* peer) {

    ecs::Entity player = EntityFactory::createPlayer(getRegistry(), 100.0f, 200.0f);
    
    std::string playerUUID = player.getName();
    

    player.addComponent<NetworkComponent>({peer, 0});

    connectedPeers_.push_back(peer);
    peerInitialAck_[peer] = false;
    initialEntitiesSent_[peer] = false;

    std::cout << "Client connected: " << peer->connectID << std::endl;
    sendPlayerId(peer, playerUUID);
    
    getRegistry().getSystem<NetworkSendSystem>().sendInitialEntities(peer);
}


void ServerNetworkManager::onUpdate(float deltaTime) {
    (void)deltaTime; // not used

    if (!host_ || gameOver_) return;

    ENetEvent event;
    enet_host_flush(host_);

    broadcastGameState(); //faudrait mettre un timer pour pas l'envoyer tout le temps

    while (enet_host_service(host_, &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                handleNewConnection(event.peer);
                break;

            case ENET_EVENT_TYPE_RECEIVE: {
                uint16_t packetType = event.packet->data[0];
                const uint8_t* payload = event.packet->data + 1;
                size_t payloadSize = event.packet->dataLength - 1;

                if (packetType == PACKET_INITIAL_ACK) {
                    processInitialAck(event.peer);
                } else if (packetType == PACKET_INPUT) {
                    uint16_t inputFlags = 0;
                    if (payloadSize >= sizeof(uint16_t)) {
                        std::memcpy(&inputFlags, payload, sizeof(uint16_t));
                    }
                    getRegistry().getSystem<NetworkReceiveSystem>()
                        .processInputCommand(inputFlags, event.peer);
                }
                enet_packet_destroy(event.packet);
                break;
            }

            case ENET_EVENT_TYPE_DISCONNECT: {
                std::cout << "Client disconnected: " << event.peer->connectID << std::endl;

                forEach([&](ecs::Entity& entity) {
                    auto& netC = entity.getComponent<NetworkComponent>();
                    if (netC.peer == event.peer) {
                        std::string removedEntityUUID = entity.getName();

                        entity.remove();

                        broadcastEntityRemoval(removedEntityUUID);
                    }
                });

                connectedPeers_.erase(std::remove(connectedPeers_.begin(), connectedPeers_.end(), event.peer),
                                    connectedPeers_.end());
                peerInitialAck_.erase(event.peer);
                initialEntitiesSent_.erase(event.peer);
                enet_peer_reset(event.peer);
                break;
            }

            default:
                break;
        }
    }
}

void ServerNetworkManager::sendPlayerId(ENetPeer* peer, const std::string &playerUUID) {
    std::array<uint8_t, 16> uuidBytes = uuid::uuidStringToByteArray(playerUUID);

    uint8_t buffer[1 + 16];
    buffer[0] = PACKET_PLAYER_ID;
    std::memcpy(buffer + 1, uuidBytes.data(), 16);

    ENetPacket* packet = enet_packet_create(buffer, sizeof(buffer), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(host_);
}


void ServerNetworkManager::processInitialAck(ENetPeer* fromPeer) {
    std::cout << "Received INITIAL_ACK from peer: " << fromPeer->connectID << std::endl;
    peerInitialAck_[fromPeer] = true;
}

void ServerNetworkManager::broadcastEntityRemoval(const std::string &entityUUID) {
    std::array<uint8_t, 16> uuidBytes = uuid::uuidStringToByteArray(entityUUID);
    std::vector<uint8_t> buffer;
    buffer.reserve(1 + uuidBytes.size());
    buffer.push_back(PACKET_ENTITY_REMOVE);
    buffer.insert(buffer.end(), uuidBytes.begin(), uuidBytes.end());
    ENetPacket* packet = enet_packet_create(buffer.data(), buffer.size(), ENET_PACKET_FLAG_RELIABLE);

    for (auto& peer : connectedPeers_) {
        enet_peer_send(peer, 0, packet);
    }
    enet_host_flush(host_);

    std::cout << "Broadcasted removal of Entity UUID: " << entityUUID << std::endl;
}

void ServerNetworkManager::sendInitialEntities(ENetPeer* peer, const std::vector<EntityState>& states) {

    const uint16_t count = static_cast<uint16_t>(states.size());

    std::vector<uint8_t> data;
    data.reserve(1 + 2 + states.size() * sizeof(EntityState));

    data.push_back(PACKET_INITIAL_ENTITIES);

    auto countPtr = reinterpret_cast<const uint8_t*>(&count);
    data.insert(data.end(), countPtr, countPtr + sizeof(uint16_t));

    for (auto& st : states) {
        auto ptr = reinterpret_cast<const uint8_t*>(&st);
        data.insert(data.end(), ptr, ptr + sizeof(EntityState));
    }

    ENetPacket* packet = enet_packet_create(data.data(), data.size(), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);
    enet_host_flush(host_);
}

void ServerNetworkManager::sendEntityUpdates(const std::vector<EntityState>& states) {
    const uint16_t count = static_cast<uint16_t>(states.size());

    std::vector<uint8_t> data;
    data.reserve(1 + 2 + states.size() * sizeof(EntityState));

    data.push_back(PACKET_ENTITY_UPDATE);

    auto countPtr = reinterpret_cast<const uint8_t*>(&count);
    data.insert(data.end(), countPtr, countPtr + sizeof(uint16_t));

    for (auto& st : states) {
        auto ptr = reinterpret_cast<const uint8_t*>(&st);
        data.insert(data.end(), ptr, ptr + sizeof(EntityState));
    }

    ENetPacket* packet = enet_packet_create(data.data(), data.size(), ENET_PACKET_FLAG_UNSEQUENCED);
    for (auto& peer : connectedPeers_) {
        enet_peer_send(peer, 0, packet);
    }
    enet_host_flush(host_);
}

void ServerNetworkManager::broadcastGameState() {
    int playerHealth = 0;
    bool foundPlayer = false;

    forEach([&](ecs::Entity& entity) {
        if (entity.getComponent<typeComponent>().type == EntityType::PLAYER) {
            playerHealth = entity.getComponent<Health>().current;
            foundPlayer = true;
        }
    });
    if (!foundPlayer) {
        //std::cerr << "Aucun joueur trouvé pour transmettre l'état de jeu." << std::endl;
        return;
    }
    
    auto& spawnSystem = getRegistry().getSystem<SpawnFromConfigSystem>();
    uint16_t currentWave = static_cast<uint16_t>(spawnSystem.getCurrentWave());
    
    uint8_t buffer[1 + sizeof(uint16_t) + sizeof(int)] = {0};
    buffer[0] = PACKET_GAME_STATE;
    std::memcpy(buffer + 1, &currentWave, sizeof(uint16_t));
    std::memcpy(buffer + 1 + sizeof(uint16_t), &playerHealth, sizeof(int));

    ENetPacket* packet = enet_packet_create(buffer, sizeof(buffer), ENET_PACKET_FLAG_RELIABLE);
    for (auto& peer : connectedPeers_) {
        enet_peer_send(peer, 0, packet);
    }
    enet_host_flush(host_);
}

void ServerNetworkManager::handleHitProjectileEnemy(size_t, size_t) {}
void ServerNetworkManager::detectHits() {}
void ServerNetworkManager::handleHit(size_t, size_t) {}
