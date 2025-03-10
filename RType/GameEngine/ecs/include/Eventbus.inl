/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** Eventbus
*/

#ifndef EVENTBUS_INL_
#define EVENTBUS_INL_

#include "Eventbus.hpp"

template <class Event>
void ecs::Eventbus::subscribe(EventCallback callback)
{
    auto type = std::type_index(typeid(Event));

    _subscribers[type].push_back(std::move(callback));
}

template <class Event>
void ecs::Eventbus::post(const Event &event)
{
    auto type = std::type_index(typeid(Event));

    auto it = _subscribers.find(type);
    if (it != _subscribers.end())
        for (const auto & callback : it->second)
            callback(event);
}

#endif /* !EVENTBUS_INL_ */