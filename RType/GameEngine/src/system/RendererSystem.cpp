/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** RendererSystem
*/

#define SDL_MAIN_HANDLED
#include "RendererSystem.hpp"
#include "ecs.hpp"
#include "typeComponent.hpp"
#include "component.hpp"
#include "event/WindowResizeEvent.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include "WindowCloseEvent.hpp"
#include "CommonLib/GameStateComponent.hpp"

RendererSystem::RendererSystem(std::string title, std::unordered_map<std::size_t, RenderableInfos> texture)
    : _title(title), _textures(texture)
{
    getFilter().require<position>();
    getFilter().require<RenderableComponent>();
}

RendererSystem::~RendererSystem() = default;

// Initialize the renderer
void RendererSystem::onStart() {
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error("Video sub-system not initialize");

    window_ = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window_) {
        throw std::runtime_error("Failed to create SDL window: " + std::string(SDL_GetError()));
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
        throw std::runtime_error("Renderer not initialized");
    }

    SDL_RenderSetLogicalSize(renderer_, 1280, 720);

    // SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_NONE);

    getRegistry().getEventbus().subscribe<TabPressedEvent>([this](const ecs::Event&) {
        cycleFilter();
    });

    // Load textures
    std::string rtypePath = std::getenv("PWD");

    if (TTF_Init() == -1) {
        throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
    }
    font_ = TTF_OpenFont((rtypePath + "/assets/Honella.otf").c_str(), 48);
    if (!font_) {
        throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
    }

    for (auto &[_, textureInfo] : _textures)
        textureInfo.texture = loadTexture(rtypePath + textureInfo.texturePath);

    // getRegistry().getEventbus().subscribe<WindowResizeEvent>([&](const ecs::Event &event) {
    //     const WindowResizeEvent &windowEvent = static_cast<const WindowResizeEvent&>(event);

    //     std::cout << "resize window: " << " widht: " << windowEvent.newWidth << " height: " << windowEvent.newHeight << std::endl;
    //     SDL_RenderSetLogicalSize(renderer_, windowEvent.newWidth, windowEvent.newHeight);
    // });
}

// Clear the renderer
void RendererSystem::clear() {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

// Display the renderer
void RendererSystem::display() {
    SDL_RenderPresent(renderer_);
}

void RendererSystem::updateAnimation(const RenderableComponent& renderable, float deltaTime) {
    auto it = _textures.find(renderable.textureId);
    if (it == _textures.end())
        return;

    RenderableInfos& textureInfo = it->second;

    if (textureInfo.frameCount <= 1)
        return;

    textureInfo.animationTime += deltaTime;

    if (textureInfo.animationTime >= textureInfo.frameDuration) {
        textureInfo.currentFrame = (textureInfo.currentFrame + 1) % textureInfo.frameCount;
        textureInfo.animationTime -= textureInfo.frameDuration;
    }
}

void RendererSystem::drawEntity(float x, float y, const RenderableComponent& renderable, float deltaTime) {
    auto it = _textures.find(renderable.textureId);
    if (it == _textures.end()) {
        std::cerr << "Erreur, pas de texture" << std::endl;
        return;
    }

    RenderableInfos& textureInfo = it->second;

    updateAnimation(renderable, deltaTime);

    SDL_Rect src = {
        textureInfo.currentFrame * textureInfo.frameWidth,
        0,
        textureInfo.frameWidth,
        textureInfo.frameHeight
    };

    SDL_Rect dest = {
        static_cast<int>(x),
        static_cast<int>(y),
        static_cast<int>(textureInfo.frameWidth * textureInfo.scale),
        static_cast<int>(textureInfo.frameHeight * textureInfo.scale)
    };

    applyColorFilter(textureInfo.texture);

    SDL_RenderCopy(renderer_, textureInfo.texture, &src, &dest);
}


// Load a texture
SDL_Texture* RendererSystem::loadTexture(const std::string& path) {
    SDL_RWops* rw = SDL_RWFromFile(path.c_str(), "rb");
    if (!rw) {
        std::cerr << "Failed to open file " << path << ": " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Surface* surface = IMG_LoadPNG_RW(rw);
    SDL_RWclose(rw);

    // if the surface is null, try to load it as a BMP
    if (!surface) {
        std::cerr << "Failed to load PNG " << path << ": " << IMG_GetError() << std::endl;
        return nullptr;
    }

    // create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_FreeSurface(surface);

    // if the texture is null, print an error
    if (!texture) {
        std::cerr << "Failed to create texture from " << path << ": " << SDL_GetError() << std::endl;
    }

    return texture;
}

void RendererSystem::cycleFilter() {
    switch (currentFilter) {
        case ColorFilter::NORMAL: currentFilter = ColorFilter::PROTANOPIA; break;
        case ColorFilter::PROTANOPIA: currentFilter = ColorFilter::DEUTERANOPIA; break;
        case ColorFilter::DEUTERANOPIA: currentFilter = ColorFilter::TRITANOPIA; break;
        case ColorFilter::TRITANOPIA: currentFilter = ColorFilter::GRAYSCALE; break;
        case ColorFilter::GRAYSCALE: currentFilter = ColorFilter::NORMAL; break;
    }
    std::cout << "Filter changed to " << static_cast<int>(currentFilter) << std::endl;
}

void RendererSystem::applyColorFilter(SDL_Texture* texture) {
    switch (currentFilter) {
        case ColorFilter::PROTANOPIA:
            SDL_SetTextureColorMod(texture, 200, 255, 255);
            break;
        case ColorFilter::DEUTERANOPIA:
            SDL_SetTextureColorMod(texture, 255, 200, 255);
            break;
        case ColorFilter::TRITANOPIA:
            SDL_SetTextureColorMod(texture, 255, 255, 200);
            break;
        case ColorFilter::VIBRANT:
            SDL_SetTextureColorMod(texture, 255, 180, 180);
            break;
        case ColorFilter::GRAYSCALE:
            SDL_SetTextureColorMod(texture, 128, 128, 128);
            break;
        case ColorFilter::NORMAL:
        default:
            SDL_SetTextureColorMod(texture, 255, 255, 255);
            break;
    }
}

void RendererSystem::drawText(const std::string& text, int x, int y) {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font_, text.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect dest = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer_, texture, nullptr, &dest);

    SDL_DestroyTexture(texture);
}

void RendererSystem::onShutdown() {
    for (auto &[_, texture] : _textures) {
        if (texture.texture) {
            SDL_DestroyTexture(texture.texture);
            texture.texture = nullptr;
        }
    }
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void RendererSystem::onUpdate(float deltaTime) {
    clear();
    forEach([&](ecs::Entity& entity) {
        auto& pos = entity.getComponent<position>();
        auto& renderable = entity.getComponent<RenderableComponent>();
        drawEntity(pos.x, pos.y, renderable, deltaTime);
    });

    auto maybeGlobal = getRegistry().getEntity("GlobalState");
    if (maybeGlobal.has_value()) {
        auto &gameState = maybeGlobal.value().getComponent<GameStateComponent>();
        drawText("Level : " + std::to_string(gameState.currentWave), 10, 10);
        drawText("PV : " + std::to_string(gameState.playerHealth), 1100, 10);
    }

    display();
}