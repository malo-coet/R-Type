/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** ParalaxResetSystem
*/

#include "systems/ParalaxResetSystem.hpp"
#include "components/typeComponent.hpp"
#include "components/component.hpp"
#include "CommonLib/FactionComponent.hpp"

ParalaxResetSystem::ParalaxResetSystem()
{
    getFilter().require<typeComponent>();
    getFilter().require<FactionParalax>();
}

ParalaxResetSystem::~ParalaxResetSystem() = default;

void ParalaxResetSystem::onUpdate(float deltaTime)
{
    forEach([deltaTime](ecs::Entity &entity) {
        auto &pos = entity.getComponent<position>();
        auto &vel = entity.getComponent<velocity>();
        auto &type = entity.getComponent<typeComponent>();
        if (type.type == PARALAX || type.type == PARALAX_TWO) {
            if (pos.x <= -2720)
                pos.x = 0;
        }
    });
}