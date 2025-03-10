/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** SpawnAsteroidSystem
*/

#include "systems/SpawnAsteroidSystem.hpp"
#include "components/typeComponent.hpp"
#include "components/component.hpp"
#include "CommonLib/factory/EntityFactory.hpp"

SpawnAsteroidSystem::SpawnAsteroidSystem()
{
}

SpawnAsteroidSystem::~SpawnAsteroidSystem() = default;

void SpawnAsteroidSystem::onUpdate(float deltaTime)
{
    static int delay = 800;

    if (delay == 0) {
        delay = 800;
        EntityFactory::createProjectileAsteroid(getRegistry(), 1500, ((std::rand() % 701) - 200), ((std::rand() % 401) - 200), 0.0f);
        std::cout << "creating asteroid" << std::endl;
    } else {
        delay--;
    }
}
