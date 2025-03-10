/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** EntityFactory
*/

#ifndef ENTITY_FACTORY_HPP_
#define ENTITY_FACTORY_HPP_

#include "ecs.hpp"
#include "components/component.hpp"
#include "components/typeComponent.hpp"
#include "gunScript.hpp"
#include <array>
#include <cstdint>

/**
 * @class EntityFactory
 * @brief Utility class for creating various types of entities in the ECS framework.
 *
 * The `EntityFactory` class provides static methods to create and initialize common game entities
 * such as players, enemies, and projectiles. It simplifies entity creation by centralizing
 * the logic for configuring components and initial states.
 */
class EntityFactory {
public:

    /**
     * @struct EntityState
     * @brief Represents the state of an entity.
     *
     * This structure contains information about an entity's attributes, such as position,
     * velocity, and type. It can be used for saving or restoring entities.
     */
    struct EntityState {
        std::array<uint8_t, 16> entityId;   ///< Unique identifier of the entity.
        float x, y;                         ///< Position of the entity.
        float dx, dy;                       ///< Velocity of the entity.
        uint32_t entityType;                ///< Type identifier for the entity.
    };

    /**
     * @brief Create a player entity and add it to the registry.
     *
     * @param registry Reference to the ECS registry.
     * @param x Initial x-coordinate of the player.
     * @param y Initial y-coordinate of the player.
     * @param vx Initial x-velocity of the player (default is 0.0f).
     * @param vy Initial y-velocity of the player (default is 0.0f).
     * @return The created player entity.
     */
    static ecs::Entity createPlayer(ecs::Registry& registry, float x, float y, float vx = 0.0f, float vy = 0.0f);

    static ecs::Entity creatBackground(ecs::Registry& registry, float x, float y);

    /**
     * @brief Create a paralax entity and add it to the registry.
     *
     * @param registry Reference to the ECS registry.
     * @param x Initial x-coordinate of the player.
     * @param y Initial y-coordinate of the player.
     * @param vx Initial x-velocity of the player (default is 0.0f).
     * @param vy Initial y-velocity of the player (default is 0.0f).
     * @return The created player entity.
     */
    static ecs::Entity createParalax(ecs::Registry& registry, float x, float y, float vx = 0.0f, float vy = 0.0f);

    /**
     * @brief Create a paralax entity and add it to the registry.
     *
     * @param registry Reference to the ECS registry.
     * @param x Initial x-coordinate of the player.
     * @param y Initial y-coordinate of the player.
     * @param vx Initial x-velocity of the player (default is 0.0f).
     * @param vy Initial y-velocity of the player (default is 0.0f).
     * @return The created player entity.
     */
    static ecs::Entity createParalaxTwo(ecs::Registry& registry, float x, float y, float vx = 0.0f, float vy = 0.0f);


    /**
     * @brief Create an enemy entity and add it to the registry.
     *
     * @param registry Reference to the ECS registry.
     * @param x Initial x-coordinate of the enemy.
     * @param y Initial y-coordinate of the enemy.
     * @param vx Initial x-velocity of the enemy (default is 0.0f).
     * @param vy Initial y-velocity of the enemy (default is 0.0f).
     * @return The created enemy entity.
     */
    static ecs::Entity createEnemy(ecs::Registry& registry, float x, float y, float vx = 0.0f, float vy = 0.0f);

    /**
     * @brief Create a medium enemy entity and add it to the registry.
     *
     * @param registry Reference to the ECS registry.
     * @param x Initial x-coordinate of the medium enemy.
     * @param y Initial y-coordinate of the medium enemy.
     * @param vx Initial x-velocity of the medium enemy (default is 0.0f).
     * @param vy Initial y-velocity of the medium enemy (default is 0.0f).
     * @return The created medium enemy entity.
     */
    static ecs::Entity createEnemyMed(ecs::Registry& registry, float x, float y, float vx = 0.0f, float vy = 0.0f);

    /**
     * @brief Create a large enemy entity and add it to the registry.
     *
     * @param registry Reference to the ECS registry.
     * @param x Initial x-coordinate of the large enemy.
     * @param y Initial y-coordinate of the large enemy.
     * @param vx Initial x-velocity of the large enemy (default is 0.0f).
     * @param vy Initial y-velocity of the large enemy (default is 0.0f).
     * @return The created large enemy entity.
     */
    static ecs::Entity createEnemyBig(ecs::Registry& registry, float x, float y, float vx = 0.0f, float vy = 0.0f);

    /**
     * @brief Create a projectile entity and add it to the registry.
     *
     * @param registry Reference to the ECS registry.
     * @param x Initial x-coordinate of the projectile.
     * @param y Initial y-coordinate of the projectile.
     * @param vx Initial x-velocity of the projectile.
     * @param vy Initial y-velocity of the projectile.
     * @return The created projectile entity.
     */
    static ecs::Entity createProjectile(ecs::Registry& registry, float x, float y, float vx, float vy);


    /**
     * @brief Create a enemy projectile entity and add it to the registry.
     *
     * @param registry Reference to the ECS registry.
     * @param x Initial x-coordinate of the projectile.
     * @param y Initial y-coordinate of the projectile.
     * @param vx Initial x-velocity of the projectile.
     * @param vy Initial y-velocity of the projectile.
     * @return The created projectile entity.
     */
    static ecs::Entity createProjectileEnemy(ecs::Registry& registry, float x, float y, float vx, float vy);

    /**
     * @brief Create a enemy projectile asteroid entity and add it to the registry.
     *
     * @param registry Reference to the ECS registry.
     * @param x Initial x-coordinate of the projectile.
     * @param y Initial y-coordinate of the projectile.
     * @param vx Initial x-velocity of the projectile.
     * @param vy Initial y-velocity of the projectile.
     * @return The created projectile entity.
     */
    static ecs::Entity createProjectileAsteroid(ecs::Registry& registry, float x, float y, float vx, float vy);


    /**
     * @brief Create an entity from a saved state and add it to the registry.
     *
     * @param registry Reference to the ECS registry.
     * @param state The saved state of the entity.
     * @return The created entity with the given state.
     */
    static ecs::Entity createEntityFromState(ecs::Registry& registry, const EntityState& state);
};

#endif /* !ENTITY_FACTORY_HPP_ */
