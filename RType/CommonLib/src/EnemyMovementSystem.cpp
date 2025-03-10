/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** EnemyMovementSystem
*/

#include "CommonLib/EnemyMovementSystem.hpp"
#include "CommonLib/FactionComponent.hpp"
#include "components/component.hpp"
#include "components/typeComponent.hpp"

EnemyMovementSystem::EnemyMovementSystem()
{
    getFilter().require<position>();
    getFilter().require<velocity>();
    getFilter().require<FactionEnemy>();
}

EnemyMovementSystem::~EnemyMovementSystem() = default;

void EnemyMovementSystem::onUpdate(float deltaTime)
{
    static int t = 0;
    forEach([deltaTime](ecs::Entity &entity) {
        auto &vel = entity.getComponent<velocity>();
        auto &type = entity.getComponent<typeComponent>();
        if (type.type == EntityType::ENEMY && t >= 200 || type.type == EntityType::ENEMY_MED && t >= 200) {
            vel.vx = ((std::rand() % 81) - 40);
            vel.vy = ((std::rand() % 81) - 40);
        }
    });
    if (t > 200)
        t = 0;
    t++;
}
