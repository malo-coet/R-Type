#include "ServerNetworkManager.hpp"
#include "systems/NetworkReceiveSystem.hpp"
#include "systems/NetworkSendSystem.hpp"
#include "components/networksComponents.hpp"
#include "Registry.hpp"
#include "components/typeComponent.hpp"
#include "components/component.hpp"
#include "Protocol.hpp"
#include "system/MovementSystem.hpp"
#include "CommonLib/EnemyMovementSystem.hpp"
#include "CommonLib/WindowHitboxSystem.hpp"
#include "CommonLib/EnemyShootGun.hpp"
#include "CollisionSystem.hpp"
#include "HitSystem.hpp"
#include "systems/SpawnFromConfigSystem.hpp"
#include "systems/SpawnAsteroidSystem.hpp"
#include <thread>
#include <chrono>
#include <iostream>
#include <csignal>

volatile bool running = true; // Signal handler flag

// Signal handler to catch SIGINT (Ctrl+C) and stop the server
void signalHandler(int signum) {
    std::cout << "\nInterrupt signal (" << signum << ") received. Shutting down server..." << std::endl;
    running = false;
}

int main() {
    std::signal(SIGINT, signalHandler);

    ecs::Registry registry;

    // Register components
    registry.registerComponent<position>();
    registry.registerComponent<velocity>();
    registry.registerComponent<typeComponent>();
    registry.registerComponent<Action>();
    registry.registerComponent<NetworkComponent>();

    // Add systems
    registry.addSystem<MovementSystem>(1);
    registry.addSystem<EnemyMovementSystem>(1);
    registry.addSystem<EnemyShootGun>(1);
    registry.addSystem<NetworkSendSystem>(0);
    registry.addSystem<NetworkReceiveSystem>(0);
    registry.addSystem<SpawnFromConfigSystem>(2);
    registry.addSystem<ServerNetworkManager>(0);
    registry.addSystem<CollisionSystem>(1);
    registry.addSystem<HitSystem>(1);
    registry.addSystem<SpawnAsteroidSystem>(1);
    registry.addSystem<WindowHitboxSystem>(2);

    auto lastTick = std::chrono::steady_clock::now();

    while (running) {
        auto currentTick = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTick - lastTick).count();
        lastTick = currentTick;

        registry.update(deltaTime);

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    std::cout << "Server shutting down..." << std::endl;
    return 0;
}
