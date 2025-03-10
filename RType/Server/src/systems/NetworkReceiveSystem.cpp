#include "systems/NetworkReceiveSystem.hpp"
#include "CommonLib/factory/EntityFactory.hpp"
#include "Registry.hpp"
#include "components/component.hpp"
#include "components/typeComponent.hpp"
#include "components/networksComponents.hpp"
#include "systems/NetworkSendSystem.hpp"

NetworkReceiveSystem::NetworkReceiveSystem() {
    getFilter().require<NetworkComponent>();
    getFilter().require<velocity>();
    getFilter().require<position>();
}

void NetworkReceiveSystem::onUpdate(float deltaTime) {
    // forEach([](ecs::Entity &entity) {
    //     auto& vel = entity.getComponent<velocity>();
    //     vel.vx = 0.0f;
    //     vel.vy = 0.0f;
    // });
}

void NetworkReceiveSystem::onStart() {
    registry_ = &getRegistry();
    networkManager_ = &registry_->getSystem<ServerNetworkManager>();
}

void NetworkReceiveSystem::processInputCommand(uint16_t inputFlags, ENetPeer* fromPeer) {

    if (!networkManager_ || !registry_) {
        return;
    }

    for (auto& entity : getEntities()) {
        auto& netC = entity.getComponent<NetworkComponent>();
        if (netC.peer == fromPeer) {
            auto& vel = entity.getComponent<velocity>();

            if (inputFlags & 0x01) vel.vy = -200.0f; // UP
            if (inputFlags & 0x02) vel.vy = 0.0f; // UP
            if (inputFlags & 0x04) vel.vy = 200.0f;  // DOWN
            if (inputFlags & 0x08) vel.vy = 0.0f;  // DOWN
            if (inputFlags & 0x10) vel.vx = -200.0f; // LEFT
            if (inputFlags & 0x20) vel.vx = 0.0f; // LEFT
            if (inputFlags & 0x40) vel.vx = 200.0f;  // RIGHT
            if (inputFlags & 0x80) vel.vx = 0.0f;  // RIGHT

            if (inputFlags & 0x100) {
                auto& pos = entity.getComponent<position>();
                ecs::Entity projectile = EntityFactory::createProjectile(
                    *registry_,
                    pos.x + 100,  // spawn offset
                    pos.y,
                    300.0f,      // speed
                    0.0f
                );

                int projectileId = networkManager_->nextEntityId_++;
                projectile.addComponent<NetworkComponent>({nullptr, projectileId});

                EntityState st = {
                    uuid::uuidStringToByteArray(projectile.getName()),
                    pos.x + 20,
                    pos.y,
                    300.0f,
                    0.0f,
                    static_cast<int>(EntityType::PROJECTILE)
                };
                std::vector<EntityState> newEntities = { st };
                registry_->getSystem<NetworkSendSystem>().sendEntityUpdates(newEntities);
            }
            break;
        }
    }
}
