/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** ActonMappingComponent
*/

#ifndef ACTONMAPPINGCOMPONENT_HPP_
#define ACTONMAPPINGCOMPONENT_HPP_

#include "components/InputComponent.hpp"
#include "ecs.hpp"

#include <unordered_map>
#include <functional>

struct InputAction
{
    ActionType requiredAction;
    float cooldown;
    float lastCall;
    std::function<void(ecs::Registry&, ecs::Entity&, InputInfo &info)> action;
};

struct InputMapping
{
    std::unordered_map<SDL_Keycode, InputAction> keyMap;
};


#endif /* !ACTONMAPPINGCOMPONENT_HPP_ */
