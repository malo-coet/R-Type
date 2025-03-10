/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** Entity
*/

#include "../include/Registry.hpp"
#include "../include/Entity.hpp"

ecs::Entity::Entity(Id id, Registry &registry): m_id(id), _registry(std::addressof(registry))
{
}

ecs::Entity::operator Id() const noexcept
{
	return m_id;
}

ecs::Entity::Id ecs::Entity::getId() const noexcept
{
    return m_id;
}

void ecs::Entity::removeAllComponents()
{
    _registry->removeAllComponents(m_id);
}

void ecs::Entity::enable()
{
    _registry->enableEntity(m_id);
}

void ecs::Entity::disable()
{
    return _registry->disableEntity(m_id);
}

bool ecs::Entity::isEnabled()
{
    return _registry->isEntityEnable(m_id);
}

bool ecs::Entity::isValid() const
{
    return _registry->isEntityValid(m_id);
}

std::string ecs::Entity::getName() const
{
    return _registry->getEntityName(m_id);
}

void ecs::Entity::remove()
{
    _registry->killEntity(m_id);
}