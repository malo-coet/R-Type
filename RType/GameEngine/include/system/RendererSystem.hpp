/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** RendererSystem
*/

#ifndef RENDERERSYSTEM_HPP_
#define RENDERERSYSTEM_HPP_

#include "ecs.hpp"
#include "components/component.hpp"
#include <memory>

/**
 * @class RendererSystem
 * 
 * @brief A system for rendering game entities and backgrounds in a game engine.
 * 
 * The `RendererSystem` class is an ECS (Entity-Component-System) system responsible for rendering
 * game content to the screen. This includes rendering entities, backgrounds, and handling graphical
 * operations using SDL (Simple DirectMedia Layer) for 2D graphics.
 * 
 * It inherits from the `ecs::System` class, allowing it to integrate seamlessly into the ECS architecture
 * of the game engine. The renderer system manages the creation and management of SDL window and renderer objects,
 * which are used to draw textures, shapes, and other visual elements.
 * 
 * This system also includes functionality for loading and managing textures, drawing entities to the screen,
 * and updating the screen each frame. It handles low-level rendering tasks and abstracts away the complexity
 * of interacting with SDL’s graphics API.
 * 
 * @note This system is crucial for any game that requires 2D rendering, as it controls what is displayed to
 * the player each frame.
 */
class RendererSystem : public ecs::System {
    enum class ColorFilter {
        NORMAL,
        PROTANOPIA,
        DEUTERANOPIA,
        TRITANOPIA,
        VIBRANT,
        GRAYSCALE
    };

    ColorFilter currentFilter = ColorFilter::NORMAL;
    public:
        explicit RendererSystem(std::string title, std::unordered_map<std::size_t, RenderableInfos>);
        virtual ~RendererSystem();
        void onStart() override;
        void onShutdown() override;
        void clear();
        void display();
        void drawEntity(float x, float y, const RenderableComponent& renderable, float deltaTime);
        SDL_Texture* loadTexture(const std::string& path);
        SDL_Renderer* getSDLRenderer() const { return renderer_; }
        void onUpdate(float deltaTime) override;

    private:

        std::string _title;

        SDL_Renderer* renderer_;

        SDL_Window* window_;

        std::unordered_map<std::size_t, RenderableInfos> _textures;

        SDL_Texture* backgroundTexture_ = nullptr;

        int windowWidth_ = 1280;
        int windowHeight_ = 720;

        float animationTime_ = 0.0f;
        int currentFrame_ = 0;
        const float frameDuration_ = 1.5f;

        void updateAnimation(const RenderableComponent& renderable, float deltaTime);
        void cycleFilter();
        void applyColorFilter(SDL_Texture* texture);

        TTF_Font* font_;
        void drawText(const std::string& text, int x, int y);

};

#endif /* !RENDERERSYSTEM_HPP_ */
