/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** Filter
*/

#include "../include/Filter.hpp"

void ecs::Filter::excludeNotRequire()
{
    _excludeNotRequire = true;
}

void ecs::Filter::ignoreNotRequire()
{
    _excludeNotRequire = false;
}

bool ecs::Filter::check(Mask const &mask) const
{
    for (auto const &type : _required) {
        if (mask.find(type) == mask.end())
            return false;
    }

    for (auto const &type : _excluded) {
        if (mask.find(type) != mask.end())
            return false;
    }

    if (_excludeNotRequire)
        for (auto const &type : mask) {
            if (_required.find(type) == _required.end())
                return false;
        }
    return true;
}
