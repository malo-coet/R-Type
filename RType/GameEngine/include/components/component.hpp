/*
** EPITECH PROJECT, 2024
** RType-private
** File description:
** component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#define SDL_MAIN_HANDLED
// #include <SFML/Graphics/RectangleShape.hpp>
#include <SDL2/SDL.h>
#include <stdexcept>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <ecs.hpp>
#include <SDL2/SDL_ttf.h>

struct position
{
    float x;
    float y;
};

struct velocity
{
    float vx;
    float vy;
};

// struct drawable
// {
//     sf::RectangleShape shape;
// };

struct controllable
{
};

struct RenderableInfos {
    SDL_Texture* texture;
    std::string texturePath;
    int width = 0;
    int height = 0;
    float scale = 1.0f;
    int frameWidth = 0;
    int frameHeight = 0;
    int frameCount = 1;
    float animationTime = 0;
    float frameDuration;
    int currentFrame = 0;

    // SDL_Color color = {255, 255, 255, 255};

    // RenderableComponent(int tex, int w, int h, float s = 1.0f)
    //     : textureId(tex), width(w), height(h), scale(s) {}
};

struct RenderableComponent {
    std::size_t textureId;
};

struct Action {
    void (*script)(ecs::Registry &, ecs::Entity &);
    float cooldown;
};

#endif /* !COMPONENT_HPP_ */
