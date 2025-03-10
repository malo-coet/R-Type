/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** sparse_array
*/

#ifndef SPARSE_ARRAY_INL_
#define SPARSE_ARRAY_INL_

#include "Sparse_array.hpp"

#include <vector>
#include <memory>
#include <optional>
#include <typeindex>

template <typename Component>
typename ecs::Sparse_array<Component>::value_type &
ecs::Sparse_array<Component>::operator[](typename ecs::Sparse_array<Component>::size_type idx)
{
    if (idx >= _data.size() || !_data[idx].has_value()) {
        throw std::runtime_error("No component at this index!");
    }
    return _data[idx].value(); 
}

template <typename Component>
typename ecs::Sparse_array<Component>::value_type const &
ecs::Sparse_array<Component>::operator[](typename ecs::Sparse_array<Component>::size_type idx) const
{
    if (idx >= _data.size() || !_data[idx].has_value()) {
        throw std::runtime_error("No component at this index!");
    }
    return _data[idx].value();
}

template <typename Component>
template <class... Params>
typename ecs::Sparse_array<Component>::reference_type ecs::Sparse_array<Component>::emplace_at(typename ecs::Sparse_array<Component>::size_type pos, Params&&... args)
{
    if (pos >= _data.size())
        _data.resize(pos + 1);
    _data[pos].emplace(std::forward<Params>(args)...);
    return _data[pos].value();
}

template <typename Component>
void ecs::Sparse_array<Component>::erase(typename ecs::Sparse_array<Component>::size_type pos)
{
    if (pos < _data.size())
        _data[pos].reset();
}

template <typename Component>
Component* ecs::Sparse_array<Component>::get(int entity_id)
{
    if (entity_id < 0 || entity_id >= _data.size())
        return nullptr;
    return _data[entity_id].has_value() ? &(*_data[entity_id]) : nullptr;
}

template <typename Component>
const Component* ecs::Sparse_array<Component>::get(int entity_id) const
{
    if (entity_id < 0 || entity_id >= _data.size())
        return nullptr;
    return _data[entity_id].has_value() ? &(*_data[entity_id]) : nullptr;
}

template <typename Component>
typename ecs::Sparse_array<Component>::size_type ecs::Sparse_array<Component>::get_index(typename ecs::Sparse_array<Component>::value_type const& elem) const
{
    for (size_t i = 0; i < _data.size(); ++i) {
        if (_data[i].has_value() && std::addressof(_data[i].value()) == std::addressof(elem))
            return i;
    }
    return static_cast<size_type>(-1); // Return invalid index
}

template <typename Component>
typename ecs::Sparse_array<Component>::iterator ecs::Sparse_array<Component>::begin()
{
    return _data.begin();
}

template <typename Component>
typename ecs::Sparse_array<Component>::const_iterator ecs::Sparse_array<Component>::begin() const
{
    return _data.begin();
}

template <typename Component>
typename ecs::Sparse_array<Component>::const_iterator ecs::Sparse_array<Component>::cbegin() const
{
    return _data.cbegin();
}

template <typename Component>
typename ecs::Sparse_array<Component>::iterator ecs::Sparse_array<Component>::end()
{
    return _data.end();
}

template <typename Component>
typename ecs::Sparse_array<Component>::const_iterator ecs::Sparse_array<Component>::end() const
{
    return _data.end();
}

template <typename Component>
typename ecs::Sparse_array<Component>::const_iterator ecs::Sparse_array<Component>::cend() const
{
    return _data.cend();
}

// Définition de la méthode size
template <typename Component>
typename ecs::Sparse_array<Component>::size_type ecs::Sparse_array<Component>::size() const
{
    return _data.size();
}

// Définition des méthodes insert_at
template <typename Component>
typename ecs::Sparse_array<Component>::reference_type
ecs::Sparse_array<Component>::insert_at(typename ecs::Sparse_array<Component>::size_type pos, Component const& component)
{
    if (pos >= _data.size())
        _data.resize(pos + 1);
    _data[pos] = component;
    return _data[pos].value();
}

template <typename Component>
typename ecs::Sparse_array<Component>::reference_type
ecs::Sparse_array<Component>::insert_at(typename ecs::Sparse_array<Component>::size_type pos, Component&& component)
{
    if (pos >= _data.size())
        _data.resize(pos + 1);
    _data[pos] = std::move(component);
    return _data[pos].value();
}

template <typename Component>
bool ecs::Sparse_array<Component>::contains(int entity_id) const {
    if (entity_id < 0 || entity_id >= _data.size())
        return false;
    return _data[entity_id].has_value();
}

#endif /* !SPARSE_ARRAY_INL_ */