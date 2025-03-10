/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** AudioManager
*/

#ifndef AUDIOMANAGER_HPP_
#define AUDIOMANAGER_HPP_

#include <string>
#include <unordered_map>
#include <SDL2/SDL_mixer.h>

class AudioManager {
    public:
        Mix_Chunk* loadSound(const std::string &id, const std::string &path);

        Mix_Music* loadMucsic(const std::string &id, const std::string &path);

        Mix_Chunk* getSound(const std::string &id);

        Mix_Music* getMusic(const std::string &id);

        void clear();

    private:
    std::unordered_map<std::string, Mix_Chunk*> _sounds;
    std::unordered_map<std::string, Mix_Music*> _mucics;
};

#endif /* !AUDIOMANAGER_HPP_ */
