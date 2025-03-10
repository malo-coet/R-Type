/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <limits>
#include <cstddef>
#include <string>

/**
 * @namespace ecs
 * @brief Namespace that contain classes for the ecs
*/
namespace ecs {

    class Registry;

    /**
     * @class Entity
     * @brief Entity for an ECS
     *
     * Class `Entity` can manipulte entity within the registry
     * of an ECS model (Entity-Component-System).
     * Each entity has its owd ID and
     * A list of diffrent components.
     */
    class Entity {
        public:

            /**
             * @brief Entity ID
             */
            using Id = std::size_t;

            /**
             * @brief Defautl constructor
             */
            Entity() = default;

            /**
             * @brief Deflaut destructor
             */
            ~Entity() = default;

            /**
             * @brief Constructor call by the Registry
             * @param id unique ID;
             * @param registry Reference to parent Registry
             */
            Entity(Id id, Registry &registry);

            Entity(Entity const &) = default;
		    Entity(Entity &&) noexcept = default;

            Entity &operator=(Entity const &) = default;
            Entity &operator=(Entity &&) noexcept = default;

            /**
             * @brief Inplicite conversion of an entity into its ID.
             * @return Entity ID.
             */
            operator Id() const noexcept;

            /**
             * @brief Get the ID of the entity.
             * @return Entity ID.
             */
            Id getId() const noexcept;

            /**
             * @brief Add component to the entity.
             * @tparam Component type.
             * @param c Component to add
             * @return reference to the added component.
             */
            template <typename Component>
            Component &addComponent(Component &&c);

            /**
             * @brief Add component to the entity.
             * @tparam Component parameter.
             * @param c Component to add
             * @return reference to the added component.
             */
            template <typename Component, typename... Params>
            Component &emplaceComponent(Params &&...p);

            /**
             * @brief Check if the composent exist for this entity.
             * @tparam Component to check.
             * @return 'true' if the composent exist, else 'false'.
             */
            template <typename Component>
            bool hasComponent() const;

            /**
             * @brief Get reference to a component
             * @tparam Component type.
             * @return Component reference.
             */
            template <typename Component>
            Component &getComponent();

            /**
             * @brief Get a const reference to a component.
             * @tparam Component type.
             * @return Component const reference.
             */
            template <typename Component>
            Component &getComponent() const;

            /**
             * @brief Remove a component from this entity.
             * @tparam Component type.
             */
            template <typename Component>
            void removeComponent();

            /**
             * @brief Remove all the component of this entity.
             */
            void removeAllComponents();

            /**
             * @brief Enable this entity.
             */
            void enable();

            /**
             * @brief Disable this entity.
             */
            void disable();

            /**
             * @brief Check if the entity is enable.
             */
            bool isEnabled();

            /**
             * @brief Check if this entity still exist.
             */
            bool isValid() const;

            /**
             * @brief retrieves the entity name if it has one.
             * @return Entity name.
             */
            std::string getName() const;

            /**
             * @brief Kill en the entity and set it to disable.
             */
            void remove();

        private:
        Id m_id{ 0 }; /*!< Unique ID of the entity */
        Registry* _registry{nullptr}; /*!< Reference to his parent registry  */

        friend class Registry;
    };
}

#endif /* !ENTITY_HPP_ */
