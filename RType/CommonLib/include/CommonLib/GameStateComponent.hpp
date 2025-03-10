#ifndef GAME_STATE_COMPONENT_HPP
#define GAME_STATE_COMPONENT_HPP

#include <cstdint>

struct GameStateComponent {
    uint16_t currentWave;
    int playerHealth;
};

#endif