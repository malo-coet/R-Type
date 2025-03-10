#define SDL_MAIN_HANDLED
#include "Window.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>

// Constructor
Window::Window() : window_(nullptr) {}

// Destructor
Window::~Window() {
    close();
}

// Create a window
bool Window::createWindow(const std::string& title, int width, int height) {
    window_ = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window_) {
        throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
    }

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error("Failed to init video sub-system.");

    return true;
}

// Close the window
void Window::close() {
    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}
