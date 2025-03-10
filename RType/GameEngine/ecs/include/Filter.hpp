/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** Filter
*/

#ifndef FILTER_HPP_
#define FILTER_HPP_

#include <unordered_set>
#include <typeindex>

namespace ecs {

    /**
     * @class Filter
     * @brief Manages filtering logic for entities based on their components.
     *
     * The `Filter` class allows specifying conditions to include or exclude entities
     * in systems based on their component composition. It supports requiring,
     * excluding, and ignoring specific components.
     */
    class Filter {
    public:
        /**
         * @typedef Mask
         * @brief Represents a set of component types for filtering.
         *
         * The mask is used to check if an entity matches the filter's conditions.
         */
        using Mask = std::unordered_set<std::type_index, std::hash<std::type_index>>;

        /**
         * @brief Default constructor for Filter.
         *
         * Initializes an empty filter with no requirements, exclusions, or ignored components.
         */
        Filter() noexcept = default;

        /**
         * @brief Default destructor for Filter.
         */
        ~Filter() = default;

        /**
         * @brief Copy constructor.
         * @param other The `Filter` instance to copy.
         */
        Filter(Filter const &) noexcept = default;

        /**
         * @brief Move constructor.
         * @param other The `Filter` instance to move.
         */
        Filter(Filter &&) noexcept = default;

        /**
         * @brief Checks if a given mask satisfies the filter's conditions.
         *
         * @param mask The mask to check against the filter's requirements and exclusions.
         * @return `true` if the mask matches the filter's criteria, `false` otherwise.
         */
        bool check(Mask const &mask) const;

        /**
         * @brief Excludes all components that are not explicitly required.
         *
         * Updates the filter to exclude all components not listed as required.
         */
        void excludeNotRequire();

        /**
         * @brief Ignores all components that are not explicitly required.
         *
         * Updates the filter to ignore all components not listed as required.
         */
        void ignoreNotRequire();

        /**
         * @brief Adds a component type to the required set.
         *
         * Entities must have this component to pass the filter.
         *
         * @tparam Component The type of component to require.
         */
        template <class Component>
        void require();

        /**
         * @brief Adds a component type to the excluded set.
         *
         * Entities with this component will fail the filter.
         *
         * @tparam Component The type of component to exclude.
         */
        template <class Component>
        void exclude();

        /**
         * @brief Adds a component type to the ignored set.
         *
         * The filter will ignore the presence or absence of this component.
         *
         * @tparam Component The type of component to ignore.
         */
        template <class Component>
        void ignore();

    private:
        /**
         * @brief Set of component types required by the filter.
         */
        std::unordered_set<std::type_index, std::hash<std::type_index>> _required;

        /**
         * @brief Set of component types excluded by the filter.
         */
        std::unordered_set<std::type_index, std::hash<std::type_index>> _excluded;

        /**
         * @brief Indicates whether to exclude components not explicitly required.
         */
        bool _excludeNotRequire = false;
    };
}

#include "Filter.inl"

#endif /* !FILTER_HPP_ */
