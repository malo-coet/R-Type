#pragma once

#include "System.hpp"
#include "ServerNetworkManager.hpp"

class NetworkSendSystem : public ecs::System {
public:
    NetworkSendSystem();
    ~NetworkSendSystem() = default;
    void onUpdate(float deltaTime) override;
    void onStart() override;

    void sendInitialEntities(ENetPeer* peer);
    void sendEntityUpdates(const std::vector<EntityState>& entities);

private:
    ServerNetworkManager* networkManager_ = nullptr;
    ecs::Registry* registry_ = nullptr;
};
