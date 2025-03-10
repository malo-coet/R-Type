/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** Entity
*/

#ifndef REGISTRY_INL_
#define REGISTRY_INL_

#include "Registry.hpp"
#include <iostream>

template <class Component>
ecs::Sparse_array <Component> &ecs::Registry::registerComponent()
{
    std::type_index type = getComponentTypeId<Component>();

    if (_components_arrays.find(type) == _components_arrays.end()) {
        _components_arrays[type] = Sparse_array<Component>();
        _erase_functions[type] = [](Registry& reg, Entity::Id const& e) {
            reg.getComponents<Component>().erase(e);
        };
    }
    return std::any_cast<Sparse_array<Component>&>(_components_arrays[type]);
}

template <class Component>
ecs::Sparse_array <Component> &ecs::Registry::getComponents()
{
    std::type_index type = getComponentTypeId<Component>();

    if (_components_arrays.find(type) == _components_arrays.end())
        throw std::runtime_error("Component type not registered.");
    return std::any_cast<Sparse_array<Component>&>(_components_arrays[type]);
}

template <class Component>
ecs::Sparse_array <Component> const &ecs::Registry::getComponents() const
{
    std::type_index type = getComponentTypeId<Component>();

    if (_components_arrays.find(type) == _components_arrays.end())
        throw std::runtime_error("Component type not registered.");
    return std::any_cast<const Sparse_array<Component>&>(_components_arrays.at(type));
}

template <class Component>
Component &ecs::Registry::getComponent(ecs::Entity::Id id)
{
    std::type_index type = getComponentTypeId<Component>();

    if (_components_arrays.find(type) == _components_arrays.end())
        throw std::runtime_error("Component type not registered.");

    auto& components = std::any_cast<Sparse_array<Component>&>(_components_arrays.at(type));

    auto* component = components.get(id);
    if (!component)
        throw std::runtime_error("Component not found for this entity.");

    return *component;
}

template <class Component>
Component const &ecs::Registry::getComponent(ecs::Entity::Id id) const
{
    std::type_index type = getComponentTypeId<Component>();

    if (_components_arrays.find(type) == _components_arrays.end())
        throw std::runtime_error("Component type not registered.");

    auto& components = std::any_cast<const Sparse_array<Component>&>(_components_arrays.at(type));

    auto* component = components.get(id);
    if (!component)
        throw std::runtime_error("Component not found for this entity.");

    return *component;
}

template <class Component>
bool ecs::Registry::isEntityHasComponent(Entity::Id id)
{
    std::type_index type = getComponentTypeId<Component>();

    if (_components_arrays.find(type) == _components_arrays.end())
        return false;

    auto& components = std::any_cast<const Sparse_array<Component>&>(_components_arrays.at(type));

    auto* compPtr = components.get(id);
    if (!compPtr)
        return false;

    return true;
}

template <typename Component>
Component &ecs::Registry::addComponent(ecs::Entity::Id id, Component &&c)
{
    if (id > _entities.size())
        throw std::runtime_error("Entity not found");

    RefreshEntity(id);
    auto& components = registerComponent<Component>();

    _ComponentsFilter[id].insert(getComponentTypeId<Component>());
    components.insert_at(id, std::forward<Component>(c));

    return components[id];
}


template <typename Component, typename... Params>
Component &ecs::Registry::emplaceComponent(ecs::Entity::Id id, Params &&...p)
{
    if (id > _entities.size())
        throw std::runtime_error("Entity not found");

    RefreshEntity(id);
    auto& components = registerComponent<Component>();
    _ComponentsFilter[id].insert(getComponentTypeId<Component>());
    components.emplace_at(id, std::forward<Params>(p)...);

    return components[id];
}

template <typename Component>
void ecs::Registry::removeComponent(ecs::Entity::Id id)
{
    if (id > _entities.size())
        throw std::runtime_error("Entity not found");

    RefreshEntity(id);
    auto& array = getComponents<Component>();
    array.erase(id);
    _ComponentsFilter[id].erase(getComponentTypeId<Component>());
}

template <class S, class... Args>
S &ecs::Registry::addSystem(std::size_t priority, Args &&...args)
{
    auto system = std::make_unique<S>(std::forward<Args>(args)...);

    _systems.addSystem(priority, std::move(system));

    getSystem<S>()._registry = this;

    return getSystem<S>();
}

template <class S>
bool ecs::Registry::hasSystem() const
{
    return _systems.template isExisting<S>();
}

template <class S>
void ecs::Registry::removeSystem()
{
    _systems.template removeSystem<S>();
}

template <class S>
S &ecs::Registry::getSystem()
{
    return _systems.template getSystem<S>();
}

template <class T>
std::type_index ecs::getComponentTypeId()
{
    return std::type_index(typeid(T));
}

#endif /* !REGISTRY_INL_ */