/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** Filter
*/

#ifndef FILTER_INL_
#define FILTER_INL_

#include "Filter.hpp"

template <class Component>
void ecs::Filter::require()
{
    _required.insert(std::type_index(typeid(Component)));
}

template <class Component>
void ecs::Filter::exclude()
{
    _excluded.insert(std::type_index(typeid(Component)));
}

template <class Component>
void ecs::Filter::ignore()
{
    _excluded.erase(std::type_index(typeid(Component)));
    _required.erase(std::type_index(typeid(Component)));
}

#endif /* !FILTER_INL_ */