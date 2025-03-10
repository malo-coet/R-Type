/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** spawnFromConfigSystem
*/

#ifndef SPAWNFROMCONFIGSYSTEM_HPP_
#define SPAWNFROMCONFIGSYSTEM_HPP_

#include "ecs.hpp"

class SpawnFromConfigSystem : public ecs::System {
    public:
        SpawnFromConfigSystem();
        virtual ~SpawnFromConfigSystem();

        void onStart() override;
        void onUpdate(float deltaTime) override;

        int getCurrentWave() const { return waveIndex_; }

    protected:
    private:
        struct Enemy {
            int size;
            std::pair<int, int> position;
            int number;
        };

        struct Wave {
            std::vector<Enemy> enemies;
        };
        void spawnWave(const Wave& wave);

        std::vector<Wave> waves_;
        size_t waveIndex_ = 0;
};

#endif /* !SPAWNFROMCONFIGSYSTEM_HPP_ */
