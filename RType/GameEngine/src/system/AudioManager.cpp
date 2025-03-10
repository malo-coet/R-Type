/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** AudioManager
*/

#include "AudioManager.hpp"

#include <stdexcept>

Mix_Chunk* AudioManager::loadSound(const std::string &id, const std::string &path)
{
    if (_sounds.find(id) == _sounds.end()) {
        Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
        if (!chunk)
             throw std::runtime_error("Cannot load sound: " + path + ", " + std::string(Mix_GetError()));
        _sounds[id] = chunk;
    }
    return _sounds[id];
}

Mix_Music* AudioManager::loadMucsic(const std::string &id, const std::string &path)
{
    if (_mucics.find(id) == _mucics.end()) {
        Mix_Music* music = Mix_LoadMUS(path.c_str());
        if (!music)
             throw std::runtime_error("Cannot load sound: " + path + ", " + std::string(Mix_GetError()));
        _mucics[id] = music;
    }
    return _mucics[id];
}

Mix_Chunk* AudioManager::getSound(const std::string &id)
{
    return _sounds.count(id) ? _sounds[id] : nullptr;
}

Mix_Music* AudioManager::getMusic(const std::string &id)
{
    return _mucics.count(id) ? _mucics[id] : nullptr;
}

void AudioManager::clear()
{
    for (auto &[_, sound] : _sounds)
        Mix_FreeChunk(sound);
    _sounds.clear();

    for (auto &[_, music] : _mucics)
        Mix_FreeMusic(music);
    _mucics.clear();
}