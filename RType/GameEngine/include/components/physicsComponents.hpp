/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** physicsComponents
*/

#ifndef PHYSICSCOMPONENTS_HPP_
#define PHYSICSCOMPONENTS_HPP_
#include "vectors.hpp"

struct Transfrom
{
    Vector2D position;
    float rotation;
    Vector2D scale;
};

struct Movement {
    Vector2D velocity;
    Vector2D acceleration;
    float mass;
    bool isStatic;
};

struct Hitbox
{
    Vector2D size;
};

#endif /* !PHYSICSCOMPONENTS_HPP_ */
