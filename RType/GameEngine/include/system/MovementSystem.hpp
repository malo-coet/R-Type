/*
** EPITECH PROJECT, 2025
** ecs
** File description:
** MovementSystem
*/

#ifndef MOVEMENTSYSTEM_HPP_
#define MOVEMENTSYSTEM_HPP_

#include "ecs.hpp"

/**
 * @class MovementSystem
 * 
 * @brief A system for managing movement in a game engine.
 * 
 * The `MovementSystem` class is an ECS (Entity-Component-System) system responsible for handling the movement
 * of entities within the game world. It updates the position and velocity of entities based on their movement
 * components, ensuring that entities move according to the physics and gameplay rules of the game.
 * 
 * This system typically interacts with components such as position, velocity, and acceleration, and may also
 * consider factors like gravity, friction, and user input to determine how entities move over time.
 * 
 * It inherits from the `ecs::System` class, allowing it to be integrated into the ECS architecture of the game
 * engine, and it operates continuously in sync with the game's update cycle.
 * 
 * @note This system is commonly used for managing the movement of characters, objects, projectiles, or any
 * other entities that require movement in the game world.
 */
class MovementSystem : public ecs::System {
    public:
        MovementSystem();
        virtual ~MovementSystem();

        void onUpdate(float deltaTime) override;

    protected:
    private:
};

#endif /* !MOVEMENTSYSTEM_HPP_ */
