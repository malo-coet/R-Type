/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** HitSystem
*/

#include "HitSystem.hpp"
#include "CommonLib/entitycomponents.hpp"

HitSystem::HitSystem()
{
    getFilter().require<Health>();
    getFilter().require<Damage>();
}

HitSystem::~HitSystem() = default;

void HitSystem::onUpdate(float deltaTime) {
    // Check if the target has a HealthComponent
    forEach([&](ecs::Entity& target) {
        auto& health = target.getComponent<Health>();
        auto damage = target.getComponent<Damage>(); // Assuming `typeComponent` stores damage
        health.current -= damage.amount;

        std::cout << "Target hit! Health reduced by " << damage.amount
                << ". Current health: " << health.current << "\n";

        target.removeComponent<Damage>();
        // If the target's health drops to or below zero, mark it as destroyed
        if (health.current <= 0) {
            std::cout << "Target destroyed!\n";
            target.remove(); // Assumes `destroy()` marks the entity for removal
        }
    });
}