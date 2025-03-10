/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** System_array
*/

#ifndef SYSTEM_ARRAY_INL_
#define SYSTEM_ARRAY_INL_

// #include "System_array.hpp"

#include <memory>
#include <iostream>
#include <typeinfo>
#include <stdexcept>
#include <type_traits>
#include <algorithm>

template <class S>
void ecs::System_array::addSystem(std::size_t priority, std::unique_ptr<S> &&system)
{
    if (isExisting<S>())
        removeSystem<S>();

    auto const type = getTypeId<S>();
    _priorities.insert({priority, type});

    _systems[type] = std::move(system);
    _newSystems.push_back(type);
}

template <class S>
S &ecs::System_array::getSystem()
{
    auto it = _systems.find(getTypeId<S>());

    if (it == _systems.end() || it->second == nullptr)
        throw std::runtime_error("System type does not exist.");

    return *static_cast<S*>(it->second.get());
}

template <class S>
S &ecs::System_array::getSystem() const
{
    auto it = _systems.find(getTypeId<S>());

    if (it == _systems.end() || it->second == nullptr)
        throw std::runtime_error("System does not exist.");

    return *static_cast<S*>(it->second.get());
}

template <class S>
std::size_t ecs::System_array::getSystemPriority() const
{
    std::type_index type = getTypeId<S>();

    for (const auto& [priority, typeId] : _priorities)
        if (typeId == type)
            return priority;

    throw std::runtime_error("System does not exist.");
}

template <class S>
void ecs::System_array::setSystemPriority(std::size_t newPriority)
{
    std::type_index type = getTypeId<S>();

    if (_systems.find(type) == _systems.end())
        throw std::runtime_error("System does not exist.");

    removePriority(type);
    _priorities.insert({newPriority, type});
}

template <class S>
bool ecs::System_array::isExisting()
{
    auto const it = _systems.find(getTypeId<S>());

    return it != _systems.end() && it->second != nullptr;
}

template <class S>
void ecs::System_array::removeSystem()
{
    auto const type = getTypeId<S>();

    auto system = _systems.find(type);

    if (system != _systems.end() && system->second != nullptr) {
        system->second->onShutdown();
    }

    removePriority(type);
    _systems.erase(type);
    _newSystems.erase(std::remove(_newSystems.begin(), _newSystems.end(), type));
}

template <class Func>
void  ecs::System_array::forEach(Func &&func)
{
    for (const auto& [_, typeId] : _priorities) {

        auto &system = _systems[typeId];
        if (system != nullptr) {
            try {
                func(*system);
            } catch(std::exception const &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

template <class Func>
void ecs::System_array::forEachNewSystem(Func &&func)
{
    for (const auto &typeId : _newSystems) {

        auto &system = _systems[typeId];
        if (system != nullptr) {
            try {
                func(*system);
            } catch(std::exception const &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    _newSystems.clear();
}

template <class S>
std::type_index ecs::System_array::getTypeId()
{
    static_assert(std::is_base_of<System, S>::value, "S is not a system");

    return std::type_index(typeid(S));
}

#endif // SYSTEM_ARRAY_INL