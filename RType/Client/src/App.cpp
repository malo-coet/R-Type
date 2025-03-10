#include <iostream>
#include <chrono>
#include "App.hpp"
#include "System_array.hpp"
#include "system/RendererSystem.hpp"
#include "networksComponents.hpp"
#include "system/InputSystem.hpp"
#include "systems/InputActionSystem.hpp"
#include "components/ActonMappingComponent.hpp"
#include "components/HealthComponent.hpp"
#include "system/MovementSystem.hpp"
#include "include/CollisionSystem.hpp"
#include "ClientNetworkManager.hpp"
#include "event/WindowCloseEvent.hpp"
#include "CommonLib/factory/EntityFactory.hpp"
#include "systems/ParalaxResetSystem.hpp"
#include "include/HitSystem.hpp"
#include "CommonLib/WindowHitboxSystem.hpp"
#include "system/AudioSystem.hpp"

App::App()
    : registry(),
      player_id(-1),
      is_initialized_(false) {}

App::~App() {
    destroy();
}

void App::init() {
    try {
        // Register all needed components
        registry.registerComponent<position>();
        registry.registerComponent<velocity>();
        registry.registerComponent<typeComponent>();
        registry.registerComponent<RenderableComponent>();
        registry.registerComponent<InputComponent>();
        registry.registerComponent<NetworkComponent>();
        registry.registerComponent<InputMapping>();
        registry.registerComponent<InputMappingComponent>();
        registry.registerComponent<HealthComponent>();

        // Load textures
        std::unordered_map<std::size_t, RenderableInfos> _textures;
        _textures.insert({0, {nullptr, "/assets/ship_1.png", 792, 113, 0.4f, 264, 113, 3, 0.8f, 0.2f}});
        _textures.insert({1, {nullptr, "/assets/ship_2.png", 792, 113, 0.4f, 264, 113, 3, 0.8f, 0.2f}});
        _textures.insert({2, {nullptr, "/assets/bullet.png", 68, 17, 1.5f, 34, 17, 2, 0.5f, 0.2f}});
        _textures.insert({3, {nullptr, "/assets/enemy_small.png", 66, 36, 2.1f, 33, 36, 2, 1.0f, 0.4f}});
        _textures.insert({4, {nullptr, "/assets/back.png", 272, 160, 5.0f, 272, 160, 1, 0.5f, 0.2f}});
        _textures.insert({5, {nullptr, "/assets/enemy_medium.png", 369, 155, 1.0f, 184, 155, 2, 0.8f, 1.0f}});
        _textures.insert({6, {nullptr, "/assets/enemy_boss.png", 660, 212, 3.0f, 165, 212, 3, 0.3f, 0.2f}});
        _textures.insert({7, {nullptr, "/assets/bullet_enemy.png", 102, 34, 1.5f, 34, 34, 3, 0.5f, 0.2f}});
        _textures.insert({8, {nullptr, "/assets/asteroid.png", 816, 160, 5.0f, 816, 160, 0, 0.0f, 0.0f}});
        _textures.insert({9, {nullptr, "/assets/stars.png", 816, 160, 5.0f, 816, 160, 0, 0.0f, 0.0f}});
        _textures.insert({10, {nullptr, "/assets/asteroid-proj.png", 32, 27, 5.0f, 32, 27, 0, 0.0f, 0.0f}});

        // Add systems in priority order
        registry.addSystem<RendererSystem>(1, "R-Type", _textures);
        registry.addSystem<MovementSystem>(2);
        registry.addSystem<InputActionSystem>(3);
        registry.addSystem<InputSystem>(4);
        registry.addSystem<CollisionSystem>(4);
        registry.addSystem<ClientNetworkManager>(5, "127.0.0.1", 1234);
        registry.addSystem<ParalaxResetSystem>(2);
        registry.addSystem<HitSystem>(2);
        registry.addSystem<WindowHitboxSystem>(3);
        auto &audioSystem = registry.addSystem<AudioSystem>(0);

        // audioSystem.loadMusic("music", "/audio/RTYPE.mp3");
        audioSystem.loadSound("laser", "/audio/Laser-Gun-Sound-Effect.wav");
        audioSystem.loadMusic("boss", "/audio/Monster-Roar-sound-effect.wav");

        is_initialized_ = true;
        EntityFactory::creatBackground(registry, 0, 0);
        EntityFactory::createParalaxTwo(registry, 0, 0, -70, 0);
        EntityFactory::createParalax(registry, 0, 0, -100, 0);
        std::cout << "Initialization complete. Waiting for server entities..." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Initialization failed: " << e.what() << std::endl;
        destroy();
        throw;
    }
}

void App::destroy() {
    if (is_initialized_) {
        registry.clear();
        is_initialized_ = false;
        std::cout << "App destroyed successfully." << std::endl;
    }
}

void App::run() {
    if (!is_initialized_) {
        throw std::runtime_error("App not initialized before running");
    }

    bool running = true;
    auto lastTick = std::chrono::steady_clock::now();

    registry.getEventbus().subscribe<WindowCloseEvent>([&](const ecs::Event &event) {
        running = false;
    });

    // Main loop
    while (running) {

        auto currentTick = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTick - lastTick).count();
        lastTick = currentTick;

        update(deltaTime);
    }

    destroy();
}

void App::update(float deltaTime) {
    // Then update all ECS systems
    registry.update(deltaTime);
}
