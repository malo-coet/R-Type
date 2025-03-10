/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** EnemyMovementSystem
*/

#ifndef ENEMYMOVEMENTSYSTEM_HPP_
#define ENEMYMOVEMENTSYSTEM_HPP_

#include "ecs.hpp"

/**
 * @class EnemyMovementSystem
 * @brief System responsible for handling enemy movements in the ECS framework.
 *
 * The `EnemyMovementSystem` is a specialized system that updates the movement 
 * of all entities classified as enemies. It processes the positions and velocities 
 * of enemies and applies changes based on the given delta time during each update cycle.
 */
class EnemyMovementSystem : public ecs::System {
    public:
        /**
         * @brief Construct a new EnemyMovementSystem object.
         *
         * Initializes the system and sets up any required data or state for enemy movement.
         */
        EnemyMovementSystem();

        /**
         * @brief Destroy the EnemyMovementSystem object.
         *
         * Handles cleanup of any resources allocated by the system.
         */
        virtual ~EnemyMovementSystem();

        /**
         * @brief Update the system during the game loop.
         *
         * This function is called on each frame to compute and update the movement
         * of enemies based on the time elapsed since the last update.
         *
         * @param deltaTime Time elapsed since the last update, in seconds.
         */
        void onUpdate(float deltaTime) override;

    protected:
    private:
};

#endif /* !ENEMYMOVEMENTSYSTEM_HPP_ */
