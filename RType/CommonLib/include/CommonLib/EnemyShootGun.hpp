/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** EnemyShootGun
*/

#ifndef ENEMYSHOOTGUN_HPP_
#define ENEMYSHOOTGUN_HPP_

#include "ecs.hpp"

/**
 * @class EnemyShootGun
 * @brief System responsible for managing enemy shooting behavior in the ECS framework.
 *
 * The `EnemyShootGun` system controls when and how enemies shoot during gameplay. 
 * It processes enemy entities, checks their shooting conditions, and triggers 
 * appropriate actions such as spawning projectiles.
 */
class EnemyShootGun : public ecs::System {
    public:
        /**
         * @brief Construct a new EnemyShootGun object.
         *
         * Initializes the system and sets up any required state or data for managing 
         * enemy shooting behavior.
         */
        EnemyShootGun();

        /**
         * @brief Destroy the EnemyShootGun object.
         *
         * Handles cleanup of resources or state used by the system.
         */
        virtual ~EnemyShootGun();

        /**
         * @brief Update the system during the game loop.
         *
         * This function is called on each frame to evaluate and handle enemy shooting.
         * It uses the time elapsed since the last update to determine if enemies 
         * should shoot and executes the shooting logic accordingly.
         *
         * @param deltaTime Time elapsed since the last update, in seconds.
         */
        void onUpdate(float deltaTime) override;

    protected:
    private:
};

#endif /* !ENEMYSHOOTGUN_HPP_ */
