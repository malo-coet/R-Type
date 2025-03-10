#pragma once

#include "System.hpp"
#include "ServerNetworkManager.hpp"

class NetworkReceiveSystem : public ecs::System {
public:
    NetworkReceiveSystem();
    ~NetworkReceiveSystem() = default;
    void onUpdate(float deltaTime) override;
    void onStart() override;

    void processInputCommand(uint16_t inputFlags, ENetPeer* fromPeer);

private:
    ServerNetworkManager* networkManager_ = nullptr;
    ecs::Registry* registry_ = nullptr;
};
