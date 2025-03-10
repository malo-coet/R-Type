#ifndef WINDOW_HPP
#define WINDOW_HPP

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <string>

class Window {
public:
    Window();
    ~Window();

    bool createWindow(const std::string& title, int width, int height);
    void close();

    SDL_Window* getSDLWindow() const { return window_; }  // Add this getter

private:
    SDL_Window* window_;
};

#endif // WINDOW_HPP
