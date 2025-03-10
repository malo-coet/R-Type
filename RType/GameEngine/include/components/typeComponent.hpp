/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** typeComponent
*/

#ifndef TYPECOMPONENT_HPP_
#define TYPECOMPONENT_HPP_

enum EntityType
{
    PLAYER,
    PLAYER2,
    PROJECTILE,
    ENEMY,
    BACKGROUND,
    ENEMY_MED,
    ENEMY_BIG,
    ENEMY_PROJECTILE,
    PARALAX,
    PARALAX_TWO,
    ASTEROID
};

struct typeComponent
{
    EntityType type;
};

#endif /* !TYPECOMPONENT_HPP_ */
