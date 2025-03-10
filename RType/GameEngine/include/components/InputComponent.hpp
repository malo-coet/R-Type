//Stores the current inputs for an entity

#ifndef INPUTCOMPONENT_HPP_
#define INPUTCOMPONENT_HPP_

#define SDL_MAIN_HANDLED
#include <cstdint>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <SDL2/SDL.h>

enum InputCommand : uint16_t {
    INPUT_NONE  = 0,
    INPUT_UP    = 1 << 0,
    INPUT_DOWN  = 1 << 1,
    INPUT_LEFT  = 1 << 2,
    INPUT_RIGHT = 1 << 3,
    INPUT_SPACE = 1 << 4,
    INPUT_F     = 1 << 5
};

enum class ActionType {
    PRESS,
    RELEASED,
    HOLD
};

struct InputInfo {
    ActionType type;
    uint32_t holdTime;
    bool isNewPress;
};

struct InputComponent {
    std::unordered_map<SDL_Keycode, InputInfo> currentInputs;
    std::queue<SDL_Keycode> keyLog;
    std::size_t maxHistory = 10;
};

#endif /* !INPUTCOMPONENT_HPP_ */
