/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** Entity
*/

#ifndef ENTITY_INL_
#define ENTITY_INL_

#include "Entity.hpp"
#include "Registry.hpp"

template <typename Component>
Component &ecs::Entity::addComponent(Component &&c)
{
    return _registry->template addComponent<Component>(m_id, std::forward<Component>(c));
}

template <typename Component, typename... Params>
Component &ecs::Entity::emplaceComponent(Params &&...p)
{
    return _registry->template emplaceComponent<Component>(m_id, std::forward<Params>(p)...);
}

template <typename Component>
bool ecs::Entity::hasComponent() const {
    return _registry->template isEntityHasComponent<Component>(m_id);
}

template <typename Component>
Component &ecs::Entity::getComponent()
{
    return _registry->template getComponent<Component>(m_id);
}

template <typename Component>
Component &ecs::Entity::getComponent() const
{
    return _registry->template getComponent<Component>(m_id);
}

template <typename Component>
void ecs::Entity::removeComponent()
{
    _registry->template removeComponent<Component>(m_id);
}

#endif /* !ENTITY_INL_ */