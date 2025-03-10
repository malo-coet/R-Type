/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** AudioSystem
*/

#include "AudioSystem.hpp"
#include "components/graphicsComponents.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

AudioSystem::AudioSystem()
{
    getFilter().require<AudioSystem>();

    if (SDL_InitSubSystem( SDL_INIT_AUDIO) != 0)
        throw std::runtime_error("Audio sub-system not initialize" + std::string(Mix_GetError()));

    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG))
        throw std::runtime_error("SDL_mixer could not initialize! Mix_Error: " + std::string(Mix_GetError()));
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        throw std::runtime_error("cannont init audio mixer: " + std::string(Mix_GetError()));

}

void AudioSystem::loadSound(const std::string &id, const std::string &path)
{
    _audioManager.loadSound(id, std::getenv("PWD") + path);
}

void AudioSystem::loadMusic(const std::string &id, const std::string &path)
{
    _audioManager.loadMucsic(id, std::getenv("PWD")+ path);
}

void AudioSystem::onStart()
{
    // if (SDL_InitSubSystem( SDL_INIT_AUDIO) != 0)
    //     throw std::runtime_error("Audio sub-system not initialize");

    // if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    //     throw std::runtime_error("cannont init audio mixer");
}

void AudioSystem::onShutdown()
{
    _audioManager.clear();
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void AudioSystem::onUpdate(float deltaTime)
{
    forEach([&](ecs::Entity &entity){
        auto &audio = entity.getComponent<AudioComponent>();
        if (audio.type == AudioComponent::Type::SoundEffect) {
            Mix_Chunk* sound = _audioManager.getSound(audio.soundId);
            if (sound) {
                Mix_PlayChannel(-1, sound, audio.loop ? -1 : 0);
                Mix_VolumeChunk(sound, audio.volume);
            }
        } else {
            Mix_Music* music = _audioManager.getMusic(audio.soundId);
            if (music) {
                Mix_PlayMusic(music, audio.loop ? -1 : 0);
                Mix_VolumeMusic(audio.volume);
            }
        }
    });
}