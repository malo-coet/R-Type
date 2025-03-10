#include "CollisionSystem.hpp"
#include "CommonLib/HitboxComponent.hpp"
#include "CommonLib/entitycomponents.hpp"
#include "CommonLib/FactionComponent.hpp"

CollisionSystem::CollisionSystem() {
    getFilter().require<position>();
    getFilter().require<typeComponent>();
    getFilter().require<Faction>();
    getFilter().require<Hitbox>();
}

CollisionSystem::~CollisionSystem() = default;

void CollisionSystem::onUpdate(float deltaTime) {
    forEach([&](ecs::Entity& e1) {
        forEach([&](ecs::Entity& e2) {
            auto &entFact1 = e1.getComponent<Faction>();
            auto &entFact2 = e2.getComponent<Faction>();
            if (isColliding(e1, e2, 20.0f))
                if (entFact1.fact != entFact2.fact) {
                    e2.addComponent<Damage>({1});
                }
        });
    });
}

bool CollisionSystem::isColliding(const ecs::Entity& a, const ecs::Entity& b, float threshold) {
    const auto& posA = a.getComponent<position>();
    const auto& posB = b.getComponent<position>();
    const auto& hitA = a.getComponent<Hitbox>();
    const auto& hitB = b.getComponent<Hitbox>();

    return (posA.x < posB.x + hitB.width && posB.x < posA.x + hitA.width && posA.y < posB.y + hitB.height && posB.y < posA.y + hitA.height);
}
