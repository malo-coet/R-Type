#include "systems/NetworkSendSystem.hpp"
#include "Registry.hpp"
#include "components/component.hpp"
#include "components/typeComponent.hpp"

NetworkSendSystem::NetworkSendSystem() {
    getFilter().require<position>();
    getFilter().require<velocity>();
    getFilter().require<typeComponent>();
}

void NetworkSendSystem::onStart() {
    registry_ = &getRegistry();
    networkManager_ = &registry_->getSystem<ServerNetworkManager>();
}

void NetworkSendSystem::onUpdate(float deltaTime) {
    (void)deltaTime;

    if (!networkManager_ || !registry_) return;

    std::vector<EntityState> allStates;
    forEach([&](ecs::Entity& entity) {
        const auto& pos  = entity.getComponent<position>();
        const auto& vel  = entity.getComponent<velocity>();
        const auto& type = entity.getComponent<typeComponent>();

        allStates.push_back({
            uuid::uuidStringToByteArray(entity.getName()),
            pos.x,
            pos.y,
            vel.vx,
            vel.vy,
            static_cast<int>(type.type)
        });
    });
    sendEntityUpdates(allStates);
}

void NetworkSendSystem::sendInitialEntities(ENetPeer* peer) {

    std::vector<EntityState> allStates;
    forEach([&](ecs::Entity& entity) {
        const auto& pos  = entity.getComponent<position>();
        const auto& vel  = entity.getComponent<velocity>();
        const auto& type = entity.getComponent<typeComponent>();

        allStates.push_back({
            uuid::uuidStringToByteArray(entity.getName()),
            pos.x,
            pos.y,
            vel.vx,
            vel.vy,
            static_cast<int>(type.type)
        });
    });

    networkManager_->sendInitialEntities(peer, allStates);
}

void NetworkSendSystem::sendEntityUpdates(const std::vector<EntityState>& entityStates) {
    if (!networkManager_) return;
    networkManager_->sendEntityUpdates(entityStates);
}
