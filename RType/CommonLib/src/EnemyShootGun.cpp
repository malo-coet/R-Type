/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** EnemyShootGun
*/

#include "CommonLib/EnemyShootGun.hpp"
#include "components/component.hpp"
#include "components/typeComponent.hpp"

EnemyShootGun::EnemyShootGun()
{
    getFilter().require<typeComponent>();
    getFilter().require<Action>();
}

EnemyShootGun::~EnemyShootGun() = default;

void EnemyShootGun::onUpdate(float deltaTime)
{
    static int t = 0;
    forEach([&](ecs::Entity &entity) {
        auto &type = entity.getComponent<typeComponent>();
        auto &act = entity.getComponent<Action>();
        if (type.type == EntityType::ENEMY && t > act.cooldown ||
                type.type == EntityType::ENEMY_MED && t > act.cooldown ||
                type.type == EntityType::ENEMY_BIG && t > act.cooldown) {
            act.script(getRegistry(), entity);
        }
    });
    if (t > 200)
        t = 0;
    t++;
}
