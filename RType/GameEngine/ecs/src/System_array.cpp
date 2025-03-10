/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** System_array
*/

#include "../include/System_array.hpp"

ecs::System_array::~System_array()
{
    removeAll();
}

void ecs::System_array::removeAll()
{
    forEach([&](System &system)
    {
        system.onShutdown();
    });

    _priorities.clear();
    _systems.clear();
}

void ecs::System_array::removePriority(std::type_index type)
{
    for (auto it = _priorities.begin(); it != _priorities.end();) {
        if (it->second == type)
            it = _priorities.erase(it);
        else
            ++it;
    }
}
