/*
** EPITECH PROJECT, 2025
** ecs
** File description:
** MovementSystem
*/

#include "system/MovementSystem.hpp"
#include "components/component.hpp"
#include "components/typeComponent.hpp"

MovementSystem::MovementSystem()
{
    getFilter().require<position>();
    getFilter().require<velocity>();
}

MovementSystem::~MovementSystem() = default;

void MovementSystem::onUpdate(float deltaTime)
{
    forEach([deltaTime](ecs::Entity &entity) {
        auto &pos = entity.getComponent<position>();
        auto &vel = entity.getComponent<velocity>();
        pos.x += vel.vx * deltaTime;
        pos.y += vel.vy * deltaTime;
    });
}
