#ifndef COLLISION_SYSTEM_HPP_
#define COLLISION_SYSTEM_HPP_

#include "ecs.hpp"
#include "components/component.hpp"
#include "components/typeComponent.hpp"
#include "components/HealthComponent.hpp"
#include <cmath>
#include <iostream>

/**
 * @class CollisionSystem
 * 
 * @brief A system for managing collisions in a game engine.
 * 
 * The `CollisionSystem` class is an ECS (Entity-Component-System) system responsible for handling collisions
 * between different entities in the game world. This system checks if entities collide and triggers appropriate
 * actions when collisions are detected, such as handling interactions between projectiles and targets.
 * 
 * It inherits from the `ecs::System` class, which allows it to be integrated into the ECS framework of the game engine,
 * while adhering to the lifecycle and architecture of an entity-component-based game engine.
 * 
 * This system operates continuously within the game's update loop, where it examines entities and applies the
 * collision detection rules.
 * 
 * @note This system is commonly used in games to manage interactions between moving entities, such as projectiles,
 * characters, and objects in the environment.
 */
class CollisionSystem : public ecs::System {
public:
    CollisionSystem();
    virtual ~CollisionSystem();

    void onUpdate(float deltaTime) override;

private:

    bool isColliding(const ecs::Entity& a, const ecs::Entity& b, float threshold);
};

#endif /* COLLISION_SYSTEM_HPP_ */