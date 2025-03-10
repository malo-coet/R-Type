/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** WindowHitboxSystem
*/

#include "CommonLib/WindowHitboxSystem.hpp"
#include "CommonLib/FactionComponent.hpp"
#include "components/component.hpp"
#include "components/typeComponent.hpp"

WindowHitboxSystem::WindowHitboxSystem()
{
    getFilter().require<velocity>();
}

WindowHitboxSystem::~WindowHitboxSystem() = default;

void WindowHitboxSystem::onUpdate(float deltaTime)
{
    forEach([&](ecs::Entity& ent) {
        auto& pos = ent.getComponent<position>();
        auto& vel = ent.getComponent<velocity>();
        auto& type = ent.getComponent<typeComponent>();
        if (type.type != EntityType::BACKGROUND && type.type != EntityType::PARALAX && type.type != EntityType::PARALAX_TWO) {
            if (type.type != EntityType::PROJECTILE &&
                    type.type != EntityType::ENEMY_PROJECTILE &&
                        type.type != EntityType::ASTEROID) {
                if ((pos.x + vel.vx) <= 0)
                    vel.vx += std::abs(pos.x + vel.vx);
                if ((pos.y + vel.vy) <= 0)
                    vel.vy += std::abs(pos.y + vel.vy);
                if ((pos.x + vel.vx) >= 1280)
                    vel.vx -= (pos.x + vel.vx) - 1280;
                if ((pos.y + vel.vy) >= 720)
                    vel.vy -= (pos.y + vel.vy) - 720;
            } else {
                if (pos.x <= -100)
                    ent.remove();
                if (type.type != EntityType::ASTEROID)
                    if (pos.x >= 1280)
                        ent.remove();
            }
        }
    });
}
