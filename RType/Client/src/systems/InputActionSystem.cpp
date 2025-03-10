/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** InputActionSystem
*/

#include "systems/InputActionSystem.hpp"
#include "components/ActonMappingComponent.hpp"
#include "components/component.hpp"

#include <iostream>

InputActionSystem::InputActionSystem()
{
    getFilter().require<InputMapping>();
    getFilter().require<InputComponent>();
    getFilter().require<velocity>();
}

void InputActionSystem::onStart()
{

}

void InputActionSystem::onUpdate(float deltaTime)
{
    forEach([&](ecs::Entity &entity){
        auto &input = entity.getComponent<InputComponent>();
        auto &actions = entity.getComponent<InputMapping>();
        auto &vel = entity.getComponent<velocity>();
        vel.vx = 0;
        vel.vy = 0;
        for (auto &[key, action] : actions.keyMap) {
            if (action.lastCall < action.cooldown)
                action.lastCall += deltaTime;
            auto it = input.currentInputs.find(key);
            if (it != input.currentInputs.end()) {
                if (action.lastCall >= action.cooldown) {
                    action.action(getRegistry(), entity, it->second);
                    action.lastCall -= action.cooldown;
                }
            }
        }
    });
}
