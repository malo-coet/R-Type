#include "ClientNetworkManager.hpp"
#include "Registry.hpp"
#include "Entity.hpp"
#include "CommonLib/factory/EntityFactory.hpp"
#include "CommonLib/GameStateComponent.hpp"
#include "../../Server/include/Protocol.hpp"
#include "components/ActonMappingComponent.hpp"
#include "UUID.hpp"

#include <iostream>
#include <cmath>
#include <cstring>

ClientNetworkManager::ClientNetworkManager(const std::string& adress, uint16_t port)
    : adresse_(adress), port_(port), host_(nullptr), peer_(nullptr), player_uuid_("") {}

ClientNetworkManager::~ClientNetworkManager() {
}

void ClientNetworkManager::onStart()
{
    if (enet_initialize() != 0)
        throw std::runtime_error("Failed to initialize ENet.");

    host_ = enet_host_create(nullptr, 1, 2, 0, 0);
    if (!host_)
        throw std::runtime_error("Failed to create ENet client.");

    ENetAddress address;
    enet_address_set_host(&address, adresse_.c_str());
    address.port = port_;

    peer_ = enet_host_connect(host_, &address, 2, 0);
    if (!peer_)
        throw std::runtime_error("Failed to connect to server.");

    ENetEvent event;
    if (enet_host_service(host_, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        std::cout << "Connected to server.\n";
        startPingThread();
    } else {
        enet_peer_reset(peer_);
        throw std::runtime_error("Connection to server failed");
    }

    ecs::Entity globalState = getRegistry().spawnEntity("GlobalState");
    globalState.addComponent<GameStateComponent>({0, 0});
}

void ClientNetworkManager::onShutdown()
{
    if (host_) {
        enet_host_destroy(host_);
    }
    enet_deinitialize();
}

void ClientNetworkManager::onUpdate(float deltaTime)
{
    if (!host_) return;

    ENetEvent event;
    enet_host_flush(host_);

    while (enet_host_service(host_, &event, 0) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE: {
                uint8_t packetType = event.packet->data[0];
                const uint8_t* payload = event.packet->data + 1;
                size_t payloadSize = event.packet->dataLength - 1;

                switch (packetType) {
                    case PACKET_PLAYER_ID:
                        processPlayerId(payload, payloadSize);
                        break;
                    case PACKET_INITIAL_ENTITIES:
                        processEntityUpdate(payload, payloadSize);
                        sendInitialAck();
                        break;
                    case PACKET_ENTITY_UPDATE:
                        processEntityUpdate(payload, payloadSize);
                        break;
                    case PACKET_ENTITY_REMOVE:
                        processEntityRemove(payload, payloadSize);
                        break;
                    case PACKET_GAME_STATE: {
                        if (payloadSize < sizeof(uint16_t) + sizeof(int)) {
                            std::cerr << "Paquet d'état de jeu trop petit\n";
                            break;
                        }
                        uint16_t wave;
                        int health;
                        std::memcpy(&wave, payload, sizeof(uint16_t));
                        std::memcpy(&health, payload + sizeof(uint16_t), sizeof(int));
                        
                        auto maybeGlobal = getRegistry().getEntity("GlobalState");
                        if (maybeGlobal.has_value()) {
                            maybeGlobal.value().getComponent<GameStateComponent>().currentWave = wave;
                            maybeGlobal.value().getComponent<GameStateComponent>().playerHealth = health;
                        }
                        break;
                    }
                    default:
                        std::cerr << "Unknown packet type received: " << static_cast<int>(packetType) << "\n";
                        break;
                }

                enet_packet_destroy(event.packet);
                break;
            }

            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "Disconnected from server.\n";
                stopPingThread();
                peer_ = nullptr;
                break;

            default:
                break;
        }
    }
}

void ClientNetworkManager::sendInputCommand(uint16_t inputFlags) {
    if (!peer_ || !host_) return;

    uint8_t buffer[3];
    buffer[0] = PACKET_INPUT;
    std::memcpy(buffer + 1, &inputFlags, sizeof(uint16_t));
    ENetPacket* packet = enet_packet_create(buffer, sizeof(buffer), ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);
    enet_peer_send(peer_, 0, packet);
    enet_host_flush(host_);
}

void ClientNetworkManager::sendInitialAck() {
    if (!peer_) return;

    std::cout << "Sending INITIAL_ACK to server.\n";
    uint8_t buffer[1] = {PACKET_INITIAL_ACK};
    ENetPacket* packet = enet_packet_create(buffer, sizeof(buffer), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer_, 0, packet);
    enet_host_flush(host_);
}

void ClientNetworkManager::processPlayerId(const uint8_t* data, size_t size) {
    if (size < 16) return;

    std::array<uint8_t, 16> uuidBytes;
    std::copy(data, data + 16, uuidBytes.begin());

    std::string uuidStr = uuid::byteArrayToUuidString(uuidBytes);

    setPlayerUUID(uuidStr);

    std::cout << "Received player UUID: " << uuidStr << "\n";
}

void ClientNetworkManager::processEntityUpdate(const uint8_t* data, size_t size)
{
    if (size < sizeof(uint16_t)) {
        std::cerr << "Packet is too small to contain the 'count' of EntityStates.\n";
        return;
    }

    std::unordered_map<SDL_Keycode, InputAction> _keyMap;
    _keyMap.emplace(std::make_pair(SDLK_z, InputAction{ActionType::HOLD, 0, 0, [&](ecs::Registry &registry, ecs::Entity &entity, InputInfo &info){
        if (info.isNewPress)
            sendInputCommand(0x01);
        if (info.type == ActionType::RELEASED)
            sendInputCommand(0x02);
        }}));
    _keyMap.emplace(std::make_pair(SDLK_s, InputAction{ActionType::HOLD, 0, 0, [&](ecs::Registry &registry, ecs::Entity &entity, InputInfo &info){
        if (info.isNewPress)
            sendInputCommand(0x04);
        if (info.type == ActionType::RELEASED)
            sendInputCommand(0x08);
        }}));
    _keyMap.emplace(std::make_pair(SDLK_q, InputAction{ActionType::HOLD, 0, 0, [&](ecs::Registry &registry, ecs::Entity &entity, InputInfo &info){
        if (info.isNewPress)
            sendInputCommand(0x10);
        if (info.type == ActionType::RELEASED)
            sendInputCommand(0x20);
        }}));
    _keyMap.emplace(std::make_pair(SDLK_d, InputAction{ActionType::HOLD, 0, 0, [&](ecs::Registry &registry, ecs::Entity &entity, InputInfo &info){
        if (info.isNewPress)
            sendInputCommand(0x40);
        if (info.type == ActionType::RELEASED)
            sendInputCommand(0x80);
        }}));
    _keyMap.emplace(std::make_pair(SDLK_f, InputAction{ActionType::HOLD, 0.5f, 0.5f, [&](ecs::Registry &registry, ecs::Entity &entity, InputInfo &info){sendInputCommand(0x100);}}));


    uint16_t count;
    std::memcpy(&count, data, sizeof(uint16_t));
    data += sizeof(uint16_t);
    size -= sizeof(uint16_t);

    if (size < count * sizeof(EntityState)) {
        std::cerr << "Packet is too small for " << count << " EntityState items.\n";
        return;
    }

    for (uint16_t i = 0; i < count; ++i) {
        EntityFactory::EntityState st;
        std::memcpy(&st, data + i * sizeof(EntityState), sizeof(EntityState));

        auto maybeEntity = getRegistry().getEntity(uuid::byteArrayToUuidString(st.entityId));
        if (!maybeEntity.has_value()) {
            ecs::Entity ent = EntityFactory::createEntityFromState(getRegistry(), st);

            std::cout << "Spawned new entity " << ent.getName() << " at (" 
                      << st.x << ", " << st.y << ") type=" << st.entityType << "\n";

            if (ent.getName() == player_uuid_) {
                ent.addComponent<InputComponent>({});
                ent.addComponent<InputMapping>({_keyMap});
            } else if (ent.getComponent<typeComponent>().type == EntityType::PLAYER)
                ent.addComponent<RenderableComponent>({1});
        } else {
            ecs::Entity ent = maybeEntity.value();

            if (ent.hasComponent<position>()) {
                auto &pos = ent.getComponent<position>();
                if (std::abs(pos.x - st.x) <= 25) {
                    pos.x = std::lerp(pos.x, st.x, 0.5f);
                    pos.y = std::lerp(pos.y, st.y, 0.5f);
                } else {
                    pos.x = st.x;
                    pos.y = st.y;
                }
            } else {
                ent.addComponent<position>({ st.x, st.y });
            }

            if (ent.hasComponent<velocity>()) {
                auto &vel = ent.getComponent<velocity>();
                vel.vx = st.dx;
                vel.vy = st.dy;
            } else {
                ent.addComponent<velocity>({ st.dx, st.dy });
            }

            if (!ent.hasComponent<typeComponent>()) {
                ent.addComponent<typeComponent>({ static_cast<EntityType>(st.entityType) });
            } else {
                auto &tc = ent.getComponent<typeComponent>();
                tc.type = static_cast<EntityType>(st.entityType);
            }
        }
    }
}

void ClientNetworkManager::processEntityRemove(const uint8_t* data, size_t size) {
    if (size < 16) {
        std::cerr << "Packet too small to contain UUID.\n";
        return;
    }
    std::array<uint8_t, 16> uuidBytes;
    std::copy(data, data + 16, uuidBytes.begin());
    std::string uuidStr = uuid::byteArrayToUuidString(uuidBytes);

    auto maybeEntity = getRegistry().getEntity(uuidStr);
    if (maybeEntity.has_value()) {
        maybeEntity.value().remove();
        std::cout << "Removed entity with UUID: " << uuidStr << "\n";
    } else {
        std::cerr << "Entity with UUID " << uuidStr << " not found.\n";
    }
}

int ClientNetworkManager::getClientId() const {
    return peer_ ? peer_->incomingPeerID : -1;
}

void ClientNetworkManager::printPing() const {
    if (peer_) {
        std::cout << "Ping: " << peer_->roundTripTime << " ms\n";
    } else {
        std::cerr << "No active connection to get ping.\n";
    }
}

void ClientNetworkManager::startPingThread() {
    running = true;
    pingThread = std::thread([this]() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            printPing();
        }
    });
}

void ClientNetworkManager::stopPingThread() {
    running = false;
    if (pingThread.joinable()) {
        pingThread.join();
    }
}
