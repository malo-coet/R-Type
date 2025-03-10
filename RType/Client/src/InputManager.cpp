#define SDL_MAIN_HANDLED
#include "InputManager.hpp"
#include <SDL2/SDL.h>

void InputManager::update() {
    keyState_ = SDL_GetKeyboardState(&keyCount_);
}

bool InputManager::isKeyPressed(SDL_Scancode key) const {
    return keyState_ && keyState_[key];
}

std::vector<SDL_Scancode> InputManager::getPressedKeys() const {
    std::vector<SDL_Scancode> pressedKeys;

    if (!keyState_) {
        return pressedKeys;
    }

    for (int i = 0; i < keyCount_; ++i) {
        if (keyState_[i]) {
            pressedKeys.push_back(static_cast<SDL_Scancode>(i));
        }
    }

    return pressedKeys;
}
