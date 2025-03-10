#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#pragma once

#include <cstdint>

#include "UUID.hpp"

enum PacketType : uint8_t {
    PACKET_PLAYER_ID        = 0x01,
    PACKET_INITIAL_ENTITIES = 0x02,
    PACKET_INITIAL_ACK      = 0x07,
    PACKET_ENTITY_UPDATE    = 0x03,
    PACKET_INPUT            = 0x04,
    PACKET_ENTITY_REMOVE    = 0x05,
    PACKET_GAME_STATE       = 0x06
};

struct EntityState {
    std::array<uint8_t, 16> entityId;
    float x, y;
    float vx, vy;
    int type;
    bool isYoursServ;
};

#endif