/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** System
*/

#include "../include/System.hpp"
#include "../include/Entity.hpp"
#include "../include/Registry.hpp"

#include <algorithm>

ecs::System::~System()
{
}

ecs::Registry &ecs::System::getRegistry()
{
    return *_registry;
}

ecs::Registry const &ecs::System::getRegistry() const
{
    return *_registry;
}

std::vector<ecs::Entity> const &ecs::System::getEntities() const
{
    return _enableEntities;
}

void ecs::System::attachEntity(Entity const &entity)
{
    if (getEntityStatus(entity) == EntityStatus::NotAttached) {
        _disableEntities.push_back(entity);

        onEntityAttachment(entity);
        setEntityStatus(entity, EntityStatus::disabled);
    }
}

void ecs::System::detachEntity(Entity const &entity)
{
    EntityStatus const status = getEntityStatus(entity);

    if (status != EntityStatus::NotAttached) {
        if (status == EntityStatus::Enabled) {
            _enableEntities.erase(std::remove(_enableEntities.begin(), _enableEntities.end(), entity));
            onEntitydisabled(entity);
        } else
            _disableEntities.erase(std::remove(_enableEntities.begin(), _enableEntities.end(), entity));

        onEntityDettachment(entity);
        setEntityStatus(entity, EntityStatus::NotAttached);
    }
}

void ecs::System::enableEntity(Entity const &entity)
{
    if (getEntityStatus(entity) == EntityStatus::disabled) {
        _disableEntities.erase(std::remove(_disableEntities.begin(), _disableEntities.end(), entity), _disableEntities.end());
        _enableEntities.push_back(entity);

        onEntityEnabled(entity);
        setEntityStatus(entity, EntityStatus::Enabled);
    }
}

void ecs::System::disableEntity(Entity const &entity)
{
    if (getEntityStatus(entity) == EntityStatus::Enabled) {
        _enableEntities.erase(std::remove(_enableEntities.begin(), _enableEntities.end(), entity), _enableEntities.end());
        _disableEntities.push_back(entity);

        onEntitydisabled(entity);
        setEntityStatus(entity, EntityStatus::disabled);
    }
}

void ecs::System::detachAll()
{
    for (const auto &entity : _enableEntities) {
        onEntitydisabled(entity);
        onEntityDettachment(entity);
    }

    for (const auto &entity : _disableEntities)
        onEntityDettachment(entity);

    _enableEntities.clear();
    _disableEntities.clear();

    _entitiesStatus.clear();
}

std::size_t ecs::System::getEntityCount() const noexcept
{
    return _disableEntities.size() + _enableEntities.size();
}

void ecs::System::onStart()
{}

void ecs::System::onUpdate(float deltaTime)
{}

void ecs::System::onShutdown()
{}

void ecs::System::onEntityAttachment(Entity entity)
{}

void ecs::System::onEntityDettachment(Entity entity)
{}

void ecs::System::onEntityEnabled(Entity entity)
{}

void ecs::System::onEntitydisabled(Entity entity)
{}

ecs::System::EntityStatus ecs::System::getEntityStatus(Entity::Id id) const
{
    auto const it = _entitiesStatus.find(id);

    if (it != _entitiesStatus.end())
        return it->second;

    return EntityStatus::NotAttached;
}

void ecs::System::setEntityStatus(Entity::Id id, EntityStatus status)
{
    if (status == EntityStatus::NotAttached)
        _entitiesStatus.erase(id);
    else
        _entitiesStatus[id] = status;
}

ecs::Filter &ecs::System::getFilter()
{
    return _filer;
}