#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <vector>

class InputManager {
public:
    void update();
    bool isKeyPressed(SDL_Scancode key) const;
    std::vector<SDL_Scancode> getPressedKeys() const;

private:
    const Uint8* keyState_ = nullptr;
    int keyCount_ = 0;
};

#endif
