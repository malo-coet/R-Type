/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** sparse_array
*/

#ifndef SPARSE_ARRAY_HPP_
#define SPARSE_ARRAY_HPP_

#include <vector>
#include <memory>
#include <optional>

#include "Filter.hpp"

namespace ecs {

    /**
     * @class Sparse_array
     * @brief A dynamic container for optional components in an Entity-Component-System (ECS) architecture.
     *
     * The `Sparse_array` class provides an efficient way to store and manage components associated with entities
     * in an ECS. Each component is indexed by an entity ID, allowing sparse storage where some entities
     * may not have certain components.
     *
     * @tparam Component The type of the component stored in the sparse array.
     */
    template <typename Component>
    class Sparse_array {
    public:
        using value_type = Component;                            ///< Type of the component stored.
        using reference_type = value_type&;                     ///< Reference type to a component.
        using const_reference_type = value_type const&;         ///< Const reference type to a component.
        using container_t = std::vector<std::optional<value_type>>; ///< Internal container for storing components.
        using ComponentFilter = std::vector<Filter::Mask>;      ///< Type for component filtering (optional).
        using size_type = typename container_t::size_type;      ///< Size type for the container.
        using iterator = typename container_t::iterator;        ///< Iterator type for the container.
        using const_iterator = typename container_t::const_iterator; ///< Const iterator type for the container.
        /**
         * @brief Default constructor for `Sparse_array`.
         */
        Sparse_array() = default;

        /**
         * @brief Copy constructor.
         */
        Sparse_array(Sparse_array const&) = default;

        /**
         * @brief Move constructor.
         */
        Sparse_array(Sparse_array&&) noexcept = default;

        /**
         * @brief Default destructor.
         */
        ~Sparse_array() = default;

        /**
         * @brief Copy assignment operator.
         */
        Sparse_array& operator=(Sparse_array const&) = default;

        /**
         * @brief Move assignment operator.
         */
        Sparse_array& operator=(Sparse_array&&) noexcept = default;

        /**
         * @brief Access the component at a given index.
         *
         * @param idx Index of the component.
         * @return Reference to the component.
         * @throws std::out_of_range if the index is invalid or the component is missing.
         */
        value_type &operator[](size_type idx);

        /**
         * @brief Access the component at a given index (const version).
         *
         * @param idx Index of the component.
         * @return Const reference to the component.
         * @throws std::out_of_range if the index is invalid or the component is missing.
         */
        value_type const &operator[](size_type idx) const;

        /**
         * @brief Get an iterator to the beginning of the container.
         */
        iterator begin();

        /**
         * @brief Get a const iterator to the beginning of the container.
         */
        const_iterator begin() const;

        /**
         * @brief Get a const iterator to the beginning of the container.
         */
        const_iterator cbegin() const;

        /**
         * @brief Get an iterator to the end of the container.
         */
        iterator end();

        /**
         * @brief Get a const iterator to the end of the container.
         */
        const_iterator end() const;

        /**
         * @brief Get a const iterator to the end of the container.
         */
        const_iterator cend() const;

        /**
         * @brief Get the number of elements in the container.
         * @return The size of the container.
         */
        size_type size() const;

        /**
         * @brief Insert a component at a specific index.
         *
         * @param pos The index at which to insert the component.
         * @param component The component to insert.
         * @return Reference to the inserted component.
         */
        reference_type insert_at(size_type pos, Component const& component);

        /**
         * @brief Insert a component at a specific index (move version).
         *
         * @param pos The index at which to insert the component.
         * @param component The component to insert (moved).
         * @return Reference to the inserted component.
         */
        reference_type insert_at(size_type pos, Component&& component);

        /**
         * @brief Construct a component in-place at a specific index.
         *
         * @tparam Params Types of constructor arguments.
         * @param pos The index at which to construct the component.
         * @param args Constructor arguments for the component.
         * @return Reference to the constructed component.
         */
        template <class... Params>
        reference_type emplace_at(size_type pos, Params&&... args);

        /**
         * @brief Remove a component at a specific index.
         *
         * @param pos The index of the component to remove.
         */
        void erase(size_type pos);

        /**
         * @brief Get a pointer to the component associated with a specific entity ID.
         *
         * @param entity_id The ID of the entity.
         * @return Pointer to the component, or nullptr if it doesn't exist.
         */
        Component* get(int entity_id);

        /**
         * @brief Get a const pointer to the component associated with a specific entity ID.
         *
         * @param entity_id The ID of the entity.
         * @return Const pointer to the component, or nullptr if it doesn't exist.
         */
        const Component* get(int entity_id) const;

        /**
         * @brief Get the index of a specific component.
         *
         * @param elem The component to find.
         * @return The index of the component.
         */
        size_type get_index(value_type const& elem) const;

        /**
         * @brief Check if a component exists for a specific entity ID.
         *
         * @param entity_id The ID of the entity.
         * @return `true` if the component exists, `false` otherwise.
         */
        bool contains(int entity_id) const;

    private:
        container_t _data; ///< The internal container for components.

        // ComponentFIlter _filter;
    };
}

#include "Sparse_array.inl"

#endif /* !SPARSE_ARRAY_HPP_ */

