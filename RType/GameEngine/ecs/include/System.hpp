/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "Entity.hpp"
#include "Filter.hpp"

#include <unordered_map>
#include <vector>

namespace ecs {

    /**
     * @class System
     * @brief Represents a system in the ECS framework.
     *
     * The `System` class defines the behavior of a group of entities that share a specific
     * set of components. It processes these entities during the update phase of the ECS loop.
     */
    class System {
        public:
            /**
             * @brief Destructor for the `System` class.
             */
            ~System();

            /**
             * @brief Iterates over all entities attached to the system and applies a function.
             *
             * @tparam Func A callable object (lambda, function pointer, etc.) to apply to each entity.
             * @param function The function to apply to each entity.
             */
            template <class Func>
            void forEach(Func &&function);

            /**
             * @brief Get the registry associated with this system.
             *
             * @return Reference to the registry.
             */
            Registry &getRegistry();

            /**
             * @brief Get the registry associated with this system (const version).
             *
             * @return Const reference to the registry.
             */
            Registry const &getRegistry() const;

            /**
             * @brief Get the list of entities attached to the system.
             *
             * @return A const reference to a vector of entities.
             */
            std::vector<Entity> const &getEntities() const;

            /**
             * @brief Detach all entities from the system.
             */
            void detachAll();

            /**
             * @brief Get the count of entities currently attached to the system.
             *
             * @return Number of entities attached to the system.
             */
            std::size_t getEntityCount() const noexcept;

            /**
             * @brief Called when the system is started.
             *
             * Override this method to implement startup behavior.
             */
            virtual void onStart();

            /**
             * @brief Called every frame to update the system.
             *
             * @param deltaTime Time elapsed since the last update.
             */
            virtual void onUpdate(float deltaTime);

            /**
             * @brief Called when the system is shut down.
             *
             * Override this method to implement cleanup behavior.
             */
            virtual void onShutdown();

            /**
             * @brief Called when an entity is attached to the system.
             *
             * @param entity The entity that was attached.
             */
            virtual void onEntityAttachment(Entity entity);

            /**
             * @brief Called when an entity is detached from the system.
             *
             * @param entity The entity that was detached.
             */
            virtual void onEntityDettachment(Entity entity);

            /**
             * @brief Called when an entity attached to the system is enabled.
             *
             * @param entity The entity that was enabled.
             */
            virtual void onEntityEnabled(Entity entity);

            /**
             * @brief Called when an entity attached to the system is disabled.
             *
             * @param entity The entity that was disabled.
             */
            virtual void onEntitydisabled(Entity entity);

        protected:
            /**
             * @brief Constructor for the `System` class.
             *
             * Protected to ensure that `System` is used as a base class.
             */
            System() = default;

            /**
             * @brief Get the filter associated with this system.
             *
             * @return Reference to the filter.
             */
            Filter &getFilter();

        private:

            /**
             * @enum EntityStatus
             * @brief Represents the attachment and enabled/disabled state of an entity.
             */
            enum class EntityStatus {
                Enabled,       ///< The entity is attached and enabled.
                disabled,      ///< The entity is attached but disabled.
                NotAttached    ///< The entity is not attached to the system.
            };

            /**
             * @brief Attach an entity to the system.
             *
             * @param entity The entity to attach.
             */
            void attachEntity(Entity const &entity);

            /**
             * @brief Detach an entity from the system.
             *
             * @param entity The entity to detach.
             */
            void detachEntity(Entity const &entity);

            /**
             * @brief Enable an entity in the system.
             *
             * @param entity The entity to enable.
             */
            void enableEntity(Entity const &entity);

            /**
             * @brief Disable an entity in the system.
             *
             * @param entity The entity to disable.
             */
            void disableEntity(Entity const &entity);

            /**
             * @brief Get the current status of an entity.
             *
             * @param id The ID of the entity.
             * @return The status of the entity.
             */
            EntityStatus getEntityStatus(Entity::Id id) const;

            /**
             * @brief Set the status of an entity.
             *
             * @param id The ID of the entity.
             * @param status The new status for the entity.
             */
            void setEntityStatus(Entity::Id id, EntityStatus status);

            Registry* _registry{nullptr};  ///< Pointer to the registry associated with the system.

            std::vector<Entity> _enableEntities;   ///< List of enabled entities.
            std::vector<Entity> _disableEntities;  ///< List of disabled entities.

            std::unordered_map<Entity::Id, EntityStatus> _entitiesStatus; ///< Map of entity IDs to their statuses.

            Filter _filer; ///< Filter used to determine which entities are handled by the system.

        friend class Registry;
    };
}

#include "System.inl"

#endif /* !SYSTEM_HPP_ */
