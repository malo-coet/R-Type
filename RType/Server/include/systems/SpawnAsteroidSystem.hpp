/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** SpawnAsteroidSystem
*/

#ifndef SPAWNASTEROIDSYSTEM_HPP_
#define SPAWNASTEROIDSYSTEM_HPP_

#include "ecs.hpp"

class SpawnAsteroidSystem : public ecs::System {
    public:
        SpawnAsteroidSystem();
        ~SpawnAsteroidSystem();

        void onUpdate(float deltaTime) override;

    protected:
    private:
};

#endif /* !SPAWNASTEROIDSYSTEM_HPP_ */
