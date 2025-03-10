/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** AudioSystem
*/

#ifndef AUDIOSYSTEM_HPP_
#define AUDIOSYSTEM_HPP_

#include "ecs.hpp"
#include "AudioManager.hpp"

class AudioSystem : public ecs::System {
    public:
        AudioSystem();
        ~AudioSystem() = default;

        void loadSound(const std::string &id, const std::string &path);

        void loadMusic(const std::string &id, const std::string &path);

        void onStart() override;
        void onShutdown() override;
        void onUpdate(float deltaTime) override;

    private:
        AudioManager  _audioManager;
};

#endif /* !AUDIOSYSTEM_HPP_ */
