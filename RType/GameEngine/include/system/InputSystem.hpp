//Updates the InputComponent for each entity based on the current state of the InputManager.

#ifndef INPUT_SYSTEM_HPP_
#define INPUT_SYSTEM_HPP_

#include "ecs.hpp"
#include "InputComponent.hpp"
#include "InputMappingComponent.hpp"

/**
 * @class InputSystem
 * 
 * @brief A system for managing user input in a game engine.
 * 
 * The `InputSystem` class is an ECS (Entity-Component-System) system responsible for handling user input
 * events, such as keyboard, mouse, or gamepad inputs, and updating relevant game entities based on the input
 * received. It provides functionality to capture input actions, map them to specific commands, and trigger
 * entity behaviors accordingly.
 * 
 * It inherits from the `ecs::System` class, allowing it to be integrated into the ECS architecture of the
 * game engine and operate in sync with other game systems.
 * 
 * This system typically handles input detection, including checking for key presses, mouse movements, and
 * button clicks. It may also handle input states such as holding down a key or button, or detecting when an
 * input has been released.
 * 
 * @note This system is often used to control characters, camera movements, and triggering actions in the game.
 */
class InputSystem : public ecs::System {
    public:
        InputSystem();
        virtual ~InputSystem();

        void onStart() override;

        void onShutdown() override;

        void onUpdate(float deltaTime) override;

    private:
        InputComponent _input;
};

#endif /* !INPUT_SYSTEM_HPP_ */
