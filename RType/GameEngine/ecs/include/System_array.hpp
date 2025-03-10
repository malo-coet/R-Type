/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** System_array
*/

#ifndef SYSTEM_ARRAY_HPP_
#define SYSTEM_ARRAY_HPP_

#include <memory>
#include <functional>
#include <map>
#include <typeindex>
#include <vector>

#include "System.hpp"

namespace ecs {

    /**
     * @class System_array
     * @brief Manages a collection of systems with priorities for an ECS architecture.
     *
     * The `System_array` class provides functionality to add, retrieve, modify, and remove systems
     * in a prioritized manner. Systems can be iterated over based on their priority.
     */
    class System_array {
        public:
            /**
             * @brief Default constructor for `System_array`.
             */
            System_array() = default;

            /**
             * @brief Destructor for `System_array`.
             */
            ~System_array();

            /**
             * @brief Add a new system to the array with a specified priority.
             *
             * @tparam S The type of the system (must derive from `ecs::System`).
             * @param priority The priority of the system (higher values mean higher priority).
             * @param system A unique pointer to the system to add.
             */
            template <class S>
            void addSystem(std::size_t priority, std::unique_ptr<S> &&system);

            /**
             * @brief Get a reference to a system by type.
             *
             * @tparam S The type of the system to retrieve.
             * @return A reference to the requested system.
             */
            template <class S>
            S &getSystem();

            /**
             * @brief Get a const reference to a system by type.
             *
             * @tparam S The type of the system to retrieve.
             * @return A const reference to the requested system.
             */
            template <class S>
            S &getSystem() const;

            /**
             * @brief Get the priority of a specific system by type.
             *
             * @tparam S The type of the system.
             * @return The priority of the system.
             */
            template <class S>
            std::size_t getSystemPriority() const;

            /**
             * @brief Set a new priority for a specific system.
             *
             * @tparam S The type of the system.
             * @param priority The new priority to set.
             */
            template <class S>
            void setSystemPriority(std::size_t priority);

            /**
             * @brief Check if a system of a specific type exists in the array.
             *
             * @tparam S The type of the system to check.
             * @return `true` if the system exists, `false` otherwise.
             */
            template <class S>
            bool isExisting();

            /**
             * @brief Remove a system of a specific type from the array.
             *
             * @tparam S The type of the system to remove.
             */
            template <class S>
            void removeSystem();

            /**
             * @brief Apply a function to each system in the array.
             *
             * Systems are iterated in order of their priority (highest to lowest).
             *
             * @tparam Func A callable object to apply to each system.
             * @param func The function to apply.
             */
            template <class Func>
            void forEach(Func &&func);

            /**
             * @brief Apply a function to each newly added system.
             *
             * This only applies to systems that were recently added and not yet iterated.
             *
             * @tparam Func A callable object to apply to each new system.
             * @param func The function to apply.
             */
            template <class Func>
            void forEachNewSystem(Func &&func);

            /**
             * @brief Remove all systems from the array.
             */
            void removeAll();

        private:
            /**
             * @brief Get the type ID for a specific system type.
             *
             * @tparam S The type of the system.
             * @return A `std::type_index` representing the system type.
             */
            template <class S>
            std::type_index getTypeId();

            /**
             * @brief Remove the priority entry for a given type index.
             *
             * @param type The type index of the system to remove from priorities.
             */
            void removePriority(std::type_index type);

            std::multimap<std::size_t, std::type_index, std::greater<std::size_t>> _priorities; ///< Map of priorities to system types.
            std::unordered_map<std::type_index, std::unique_ptr<System>> _systems; ///< Map of system type indices to systems.
            std::vector<std::type_index> _newSystems; ///< List of newly added system type indices.
    };
}

#include "System_array.inl"

#endif /* !SYSTEM_ARRAY_HPP_ */
