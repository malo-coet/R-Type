#define SDL_MAIN_HANDLED
#include "InputSystem.hpp"
#include "event/WindowCloseEvent.hpp"
#include "event/WindowResizeEvent.hpp"

#include <chrono>
#include <SDL2/SDL.h>
#include <iostream>

InputSystem::InputSystem()
{
    getFilter().require<InputComponent>();
}

InputSystem::~InputSystem() = default;

void InputSystem::onStart()
{
    if (SDL_InitSubSystem(SDL_INIT_EVENTS) != 0)
        throw std::runtime_error("Failed to init event sub-system.");
}

void InputSystem::onShutdown()
{
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

void InputSystem::onUpdate(float deltaTime)
{
    SDL_Event event;

    for (auto it = _input.currentInputs.begin(); it != _input.currentInputs.end(); ) {
        if (it->second.isNewPress == true)
            it->second.isNewPress = false;
        if (it->second.type == ActionType::RELEASED)
            it = _input.currentInputs.erase(it);
        else
            ++it;
    }

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_TAB) {
                getRegistry().getEventbus().post(TabPressedEvent{});
            }
            auto &keyInfo = _input.currentInputs[event.key.keysym.sym];
            _input.keyLog.push(event.key.keysym.sym);
            if (keyInfo.type != ActionType::HOLD) {
                keyInfo.type = ActionType::PRESS;
                keyInfo.isNewPress = true;
                keyInfo.holdTime = 0;
            }
            if (_input.keyLog.size() > _input.maxHistory)
                _input.keyLog.pop();
        } else if (event.type == SDL_KEYUP)
            _input.currentInputs[event.key.keysym.sym].type = ActionType::RELEASED;
        else if (event.type == SDL_QUIT)
            getRegistry().getEventbus().post(WindowCloseEvent{});
        else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
            getRegistry().getEventbus().post(WindowResizeEvent{event.window.data1, event.window.data2});
    }

    for (auto &[key, keyInfo] : _input.currentInputs) {
        if (keyInfo.type == ActionType::HOLD || keyInfo.type == ActionType::PRESS) {
            keyInfo.holdTime += deltaTime;
            keyInfo.type = ActionType::HOLD;
        }
    }

    forEach([&](ecs::Entity &entity) {
        auto &input = entity.getComponent<InputComponent>();
        input = _input;
    });
}
