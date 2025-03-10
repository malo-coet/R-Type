/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** Registry
*/

#include "../include/Registry.hpp"
#include "../include/System_array.hpp"
#include "../include/Entity.hpp"

ecs::Registry::~Registry()
{
    clear();
}

ecs::Eventbus &ecs::Registry::getEventbus()
{
    return _events;
}

ecs::Entity ecs::Registry::spawnEntity()
{
    Entity::Id id;

    if (!_reusable_entity.empty()) {
        id = _reusable_entity.top();
        _reusable_entity.pop();
    } else {
        id = _next_entity++;
        _entities.resize(id + 1);
        _ComponentsFilter.resize(id + 1);
    }

    _entities[id].entity = Entity{id, *this};
    _entities[id].isEnabled = true;
    _entities[id].isValid = true;

    enableEntity(_entities[id].entity);

    return _entities[id].entity;
}

ecs::Entity ecs::Registry::spawnEntity(Entity::Id id)
{
    if (id <= _entities.size() && _entities[id].isValid)
        throw std::runtime_error("Entity id already used");
    if (id > _entities.size()) {
        _entities.resize(id + 1);
        _ComponentsFilter.resize(id + 1);
    }

    _entities[id].entity = Entity{id, *this};
    _entities[id].isEnabled = true;
    _entities[id].isValid = true;

    enableEntity(_entities[id].entity);

    return _entities[id].entity;
}

ecs::Entity ecs::Registry::spawnEntity(std::string name)
{
    if (_names.find(name) != _names.end())
        throw std::runtime_error("Entity name already used.");

    Entity entity{spawnEntity()};

    _names[name] = entity.getId();
    _entities[entity.getId()].name = name;

    return entity;
}

void ecs::Registry::killEntity(Entity::Id id)
{
    if (!isEntityValid(id))
        throw std::runtime_error("Entity not valid");
    _actions.push_back({id, EntityActions::Action::Remove});
}

void ecs::Registry::killAllEntity()
{
    for (auto const &entity : _entities)
        if (entity.isValid)
            killEntity(entity.entity);
}

void ecs::Registry::enableEntity(Entity::Id id)
{
    if (!isEntityValid(id))
        throw std::runtime_error("Entity not valid");
    _actions.push_back({id, EntityActions::Action::Enable});
}
void ecs::Registry::disableEntity(Entity::Id id)
{
    if (!isEntityValid(id))
        throw std::runtime_error("Entity not valid");
    _actions.push_back({id, EntityActions::Action::Disable});
}

void ecs::Registry::RefreshEntity(Entity::Id id)
{
    if (!isEntityValid(id))
        throw std::runtime_error("Entity not valid");
    _actions.push_back({id, EntityActions::Action::Refresh});
}

void ecs::Registry::removeAllSystem()
{
    _systems.removeAll();
}

void ecs::Registry::removeAllComponents(Entity::Id id)
{
    if (id >= _entities.size())
        throw std::runtime_error("Invalid entity");

    for (auto& [type, erase] : _erase_functions)
        if (erase)
            erase(*this, id);
    _ComponentsFilter[id].clear();
}

std::string ecs::Registry::getEntityName(Entity::Id id) const
{
    if (!isEntityValid(id))
        throw std::runtime_error("Invalid entity");

    if (_entities[id].name.has_value())
        return _entities[id].name.value();
    return {};
}

std::optional<ecs::Entity> ecs::Registry::getEntity(Entity::Id id) const
{
    if (!isEntityValid(id))
        return std::nullopt;

    return _entities[id].entity;
}

std::optional<ecs::Entity> ecs::Registry::getEntity(std::string const &name) const
{
    auto const it = _names.find(name);

    if (it == _names.end())
        return std::nullopt;

    return getEntity(it->second);
}

void ecs::Registry::update(float deltatTime)
{
    _systems.forEachNewSystem([](System &system){
        system.onStart();
    });

    updateEntities();

    _systems.forEach([deltatTime](System &system){
        system.onUpdate(deltatTime);
    });
}

void ecs::Registry::clear()
{
    _components_arrays.clear();
    _entities.clear();
    _actions.clear();
    _names.clear();
    _next_entity = 0;
    _reusable_entity = std::stack<Entity::Id>();
    _systems.removeAll();
    _erase_functions.clear();
}

bool ecs::Registry::isEntityEnable(Entity::Id id) const
{
    return id < _entities.size() && _entities[id].isEnabled;
}

bool ecs::Registry::isEntityValid(Entity::Id id) const
{
    return id < _entities.size() && _entities[id].isValid;
}

void ecs::Registry::updateEntities()
{
    auto const actions = std::move(_actions);
    _actions = decltype(_actions){};

    for (auto const &action : actions) {
        try {
            applyAction(action);
        } catch (std::exception const &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void ecs::Registry::tryAttach(System &system, Entity::Id id)
{
    if (system.getFilter().check(_ComponentsFilter[id])) {
        system.attachEntity(_entities[id].entity);
    } else {
        system.detachEntity(_entities[id].entity);
    }
}

void ecs::Registry::actionRemove(Entity::Id id)
{
    _systems.forEach([&](System &sytem){
        sytem.detachEntity(_entities[id].entity);
    });
    _entities[id].isValid = false;

    if (_entities[id].name.has_value()) {
        _names.erase(_entities[id].name.value());
        _entities[id].name.reset();
    }

    _reusable_entity.push(id);
    removeAllComponents(id);
}

void ecs::Registry::actionEnable(Entity::Id id)
{
    _entities[id].isEnabled = true;

    _systems.forEach([&](System &system) {
        tryAttach(system, id);

        system.enableEntity(_entities[id].entity);
    });
}

void ecs::Registry::actionDisable(Entity::Id id)
{
    _entities[id].isEnabled = false;

    _systems.forEach([&](System &system) {
        tryAttach(system, id);

        system.disableEntity(_entities[id].entity);
    });
}

void ecs::Registry::actionRefresh(Entity::Id id)
{
    _systems.forEach([&](System &system){
        tryAttach(system, id);

        if (_entities[id].isEnabled)
            system.enableEntity(_entities[id].entity);
    });
}

void ecs::Registry::applyAction(EntityActions const &action)
{
    if (!isEntityValid(action.id))
        throw std::runtime_error("Entity not valid");

    switch (action.action) {
    case EntityActions::Action::Enable:
        actionEnable(action.id);
        break;

    case EntityActions::Action::Disable:
        actionDisable(action.id);
        break;

    case EntityActions::Action::Refresh:
        actionRefresh(action.id);
        break;

    case EntityActions::Action::Remove:
        actionRemove(action.id);
        break;
    }
}
