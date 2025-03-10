/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_
#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>
#include <stack>
#include <iostream>

#include "Filter.hpp"
#include "Sparse_array.hpp"
#include "System_array.hpp"
#include "Entity.hpp"
#include "System.hpp"
#include "Eventbus.hpp"


namespace ecs {

    /**
     * @class Registry
     * @brief Core manager for the ECS architecture.
     *
     * The `Registry` class is responsible for managing entities, components, systems, and events. 
     * It provides methods for creating and destroying entities, managing their components, and 
     * updating the state of the ECS world through systems.
     */
    class Registry {
        public:
            /**
             * @brief Default constructor for Registry.
             */
            Registry() = default;

            /**
             * @brief Destructor for Registry.
             * 
             * Cleans up all resources and ensures proper removal of systems and components.
             */
            ~Registry();

            /**
             * @brief Access the Eventbus instance.
             * 
             * The Eventbus allows event-based communication within the ECS.
             * 
             * @return Reference to the `Eventbus`.
             */
            Eventbus &getEventbus();

            /**
             * @brief Add a system to the ECS with a specified priority.
             * 
             * Systems are executed in the order of their priority.
             * 
             * @tparam S Type of the system.
             * @tparam Args Arguments to construct the system.
             * @param priority Execution priority of the system.
             * @param args Arguments for constructing the system.
             * @return Reference to the newly added system.
             */
            template <class S, class... Args>
            S &addSystem(std::size_t priority, Args &&...args);

            /**
             * @brief Remove a system from the ECS.
             * 
             * @tparam S Type of the system to remove.
             */
            template <class S>
            void removeSystem();

            /**
             * @brief Remove all systems from the ECS.
             */
            void removeAllSystem();

            /**
             * @brief Retrieve a system by its type.
             * 
             * @tparam S Type of the system to retrieve.
             * @return Reference to the system.
             * @throws std::runtime_error if the system is not found.
             */
            template <class S>
            S &getSystem();

            /**
             * @brief Check if a system is registered.
             * 
             * @tparam S Type of the system to check.
             * @return `true` if the system is registered, `false` otherwise.
             */
            template <class S>
            bool hasSystem() const;

            /**
             * @brief Register a new component type in the ECS.
             * 
             * @tparam Component Type of the component to register.
             * @return Reference to the Sparse_array managing the components.
             */
            template <class Component>
            Sparse_array<Component> &registerComponent();

            /**
             * @brief Access components of a specific type.
             * 
             * @tparam Component Type of the components to access.
             * @return Reference to the Sparse_array managing the components.
             */
            template <class Component>
            Sparse_array<Component> &getComponents();

            /**
             * @brief Access components of a specific type (const version).
             * 
             * @tparam Component Type of the components to access.
             * @return Const reference to the Sparse_array managing the components.
             */
            template <class Component>
            Sparse_array<Component> const &getComponents() const;

            /**
             * @brief Retrieve a component from a specific entity.
             * 
             * @tparam Component Type of the component to retrieve.
             * @param id Entity ID.
             * @return Reference to the component.
             */
            template <class Component>
            Component &getComponent(Entity::Id id);

            /**
             * @brief Retrieve a component from a specific entity (const version).
             * 
             * @tparam Component Type of the component to retrieve.
             * @param id Entity ID.
             * @return Const reference to the component.
             */
            template <class Component>
            Component const &getComponent(Entity::Id id) const;

            /**
             * @brief Check if an entity has a specific component.
             * 
             * @tparam Component Type of the component to check.
             * @param id Entity ID.
             * @return `true` if the entity has the component, `false` otherwise.
             */
            template <class Component>
            bool isEntityHasComponent(Entity::Id id);

            /**
             * @brief Add a component to an entity.
             * 
             * @tparam Component Type of the component.
             * @param id Entity ID.
             * @param c Component to add.
             * @return Reference to the added component.
             */
            template <typename Component>
            Component &addComponent(Entity::Id id, Component &&c);

            /**
             * @brief Emplace a component for an entity.
             * 
             * @tparam Component Type of the component.
             * @tparam Params Parameters to construct the component.
             * @param id Entity ID.
             * @param p Parameters for the component constructor.
             * @return Reference to the added component.
             */
            template <typename Component, typename... Params>
            Component &emplaceComponent(Entity::Id id, Params &&...p);

            /**
             * @brief Remove a component from an entity.
             * 
             * @tparam Component Type of the component to remove.
             * @param id Entity ID.
             */
            template <typename Component>
            void removeComponent(Entity::Id id);

            /**
             * @brief Spawn a new entity.
             * 
             * @return The created entity.
             */
            Entity spawnEntity();

            /**
             * @brief Spawn an entity with a specific ID.
             * 
             * @param id ID of the entity.
             * @return The created entity.
             */
            Entity spawnEntity(Entity::Id id);

            /**
             * @brief Spawn an entity with a specific name.
             * 
             * @param name Name of the entity.
             * @return The created entity.
             */
            Entity spawnEntity(std::string name);

            /**
             * @brief Kill an entity by ID.
             * 
             * @param id ID of the entity.
             */
            void killEntity(Entity::Id id);

            /**
             * @brief Remove all entities.
             */
            void killAllEntity();

            /**
             * @brief Enable an entity.
             * 
             * @param id ID of the entity.
             */
            void enableEntity(Entity::Id id);

            /**
             * @brief Disable an entity.
             * 
             * @param id ID of the entity.
             */
            void disableEntity(Entity::Id id);

            void RefreshEntity(Entity::Id id);

            void removeAllComponents(Entity::Id id);

            std::string getEntityName(Entity::Id id) const;

            std::optional<Entity> getEntity(Entity::Id id) const;

            std::optional<Entity> getEntity(std::string const &name) const;


            /**
             * @brief Update the registry and its systems.
             * 
             * @param deltatTime Delta time since the last update.
             */
            void update(float deltatTime);

            /**
             * @brief Clear all entities, components, and systems.
             */
            void clear();

            /**
             * @brief Check if an entity is enabled.
             * 
             * @param id ID of the entity.
             * @return `true` if the entity is enabled, `false` otherwise.
             */
            bool isEntityEnable(Entity::Id id) const;

            /**
             * @brief Check if an entity is valid.
             * 
             * A valid entity exists within the ECS and has not been removed.
             * 
             * @param id ID of the entity.
             * @return `true` if the entity is valid, `false` otherwise.
             */
            bool isEntityValid(Entity::Id id) const;

        private:
            /**
             * @struct EntityAttributes
             * @brief Attributes associated with each entity.
             */
            struct EntityAttributes {
                Entity entity; ///< The entity object.
                bool isEnabled{false}; ///< Indicates if the entity is enabled.
                bool isValid{false}; ///< Indicates if the entity is valid.
                std::optional<std::string> name; ///< Optional name of the entity.
            };

            /**
             * @struct EntityActions
             * @brief Actions to be performed on entities.
             */
            struct EntityActions {
                /**
                 * @enum Action
                 * @brief Enumerates possible actions for an entity.
                 */
                enum class Action {
                    Enable, ///< Enable the entity.
                    Disable, ///< Disable the entity.
                    Refresh, ///< Refresh the entity.
                    Remove ///< Remove the entity.
                };

                Entity::Id id; ///< ID of the entity.
                Action action; ///< Action to be performed.
            };

            /**
             * @brief Attempt to attach a system to an entity.
             * 
             * @param system Reference to the system.
             * @param id ID of the entity.
             */
            void tryAttach(System &system, Entity::Id id);

            /**
             * @brief Update all entities in the registry.
             */
            void updateEntities();

            /**
             * @brief Perform the removal action for an entity.
             * 
             * @param id ID of the entity.
             */
            void actionRemove(Entity::Id id);

            /**
             * @brief Perform the enable action for an entity.
             * 
             * @param id ID of the entity.
             */
            void actionEnable(Entity::Id id);

            /**
             * @brief Perform the disable action for an entity.
             * 
             * @param id ID of the entity.
             */
            void actionDisable(Entity::Id id);

            /**
             * @brief Perform the refresh action for an entity.
             * 
             * @param id ID of the entity.
             */
            void actionRefresh(Entity::Id id);

            /**
             * @brief Apply a specified action to an entity.
             * 
             * @param action The action to apply.
             */
            void applyAction(EntityActions const &action);

            /**
             * @brief Map of registered component arrays, keyed by type.
             */
            std::unordered_map<std::type_index, std::any> _components_arrays;

            /**
             * @brief Filters applied to components.
             */
            std::vector<Filter::Mask> _ComponentsFilter;

            /**
             * @brief Attributes for all entities in the ECS.
             */
            std::vector<EntityAttributes> _entities;

            /**
             * @brief Queue of actions to apply to entities.
             */
            std::vector<EntityActions> _actions;

            /**
             * @brief Map of entity names to their IDs.
             */
            std::unordered_map<std::string, Entity::Id> _names;

            /**
             * @brief ID for the next entity to be spawned.
             */
            Entity::Id _next_entity = 0;

            /**
             * @brief Stack of reusable entity IDs.
             */
            std::stack<Entity::Id> _reusable_entity;

            /**
             * @brief Array of systems in the ECS.
             */
            System_array _systems;

            /**
             * @brief Eventbus for managing events.
             */
            Eventbus _events;

            /**
             * @brief Map of erase functions for removing components by type.
             */
            std::unordered_map<std::type_index, std::function<void(Registry &, Entity::Id const)>> _erase_functions;

            friend class Entity;
    };

    /**
     * @brief Get the type index of a component.
     * 
     * This free function is used to obtain the unique type index for a component type.
     * 
     * @tparam T Component type.
     * @return std::type_index Type index of the component.
     */
    template <class T>
    std::type_index getComponentTypeId();
}

#endif /* !REGISTRY_HPP_ */
