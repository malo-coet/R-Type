#ifndef SERVERNETWORKMANAGER_HPP
#define SERVERNETWORKMANAGER_HPP

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <vector>
#include <map>
#include <enet/enet.h>
#include "ecs.hpp"
#include "Protocol.hpp"
#include "components/component.hpp"
#include "components/networksComponents.hpp"


class ServerNetworkManager : public ecs::System {
public:
    ServerNetworkManager();
    ~ServerNetworkManager();

    // void setRegistryRef(ecs::Registry& registry);
    // void handleEvents(ecs::Registry& registry);
    void onUpdate(float deltaTime) override;
    bool initializeServer(uint16_t port);
    void onStart() override;

    void sendPlayerId(ENetPeer* peer, const std::string &playerUUID);
    void broadcastEntityRemoval(const std::string &entityUUID);
    void processInitialAck(ENetPeer* fromPeer);

    //void spawnNewEnemy(ecs::Registry& registry, int size);
    void spawnProjectile(float startX, float startY, float velocityX, float velocityY);

    void sendInitialEntities(ENetPeer* peer, const std::vector<EntityState>& states);
    void sendEntityUpdates(const std::vector<EntityState>& states);

    void handleHitProjectileEnemy(size_t projectileIndex, size_t enemyIndex);
    void detectHits();
    void broadcastGameState();
    void handleHit(size_t projectileIndex, size_t playerIndex);

    size_t getConnectedPeersCount() const { return connectedPeers_.size(); }

    int nextEntityId_ = 0;

private:
    void handleNewConnection(ENetPeer* peer);

    ENetHost* host_;
    // ecs::Registry* registryRef_;
    bool gameOver_ = false;

    std::vector<ENetPeer*> connectedPeers_;
    std::map<ENetPeer*, bool> peerInitialAck_;
    std::map<ENetPeer*, bool> initialEntitiesSent_;

    int waveIndex_ = 0;
};

#endif // SERVERNETWORKMANAGER_HPP
