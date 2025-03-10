/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** graphicsComponents
*/

#ifndef GRAPHICSCOMPONENTS_HPP_
#define GRAPHICSCOMPONENTS_HPP_

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "vector"
#include <iostream>

#include "vectors.hpp"

struct Sprite {
    SDL_Texture* texture;
    Vector2D origin;
};

struct Animation {
    std::vector<SDL_Texture*> frames;
    float frameTime;
    bool looping;
};

struct AudioComponent {
    enum class Type {
        SoundEffect, // Sound effect
        Music        // Music
    };

    Type type;
    std::string soundId;
    bool loop = false;
    int volume = SDL_MIX_MAXVOLUME;
};

#endif /* !GRAPHICSCOMPONENTS_HPP_ */
