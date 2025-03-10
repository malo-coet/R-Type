/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** UUID
*/

#include "UUID.hpp"

namespace uuid {
    std::string generate_uuid_v4() {
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 4; i++) {
            ss << dis(gen);
        }
        ss << "-4";
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        ss << dis2(gen);
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 12; i++) {
            ss << dis(gen);
        };
        return ss.str();
    }

    std::array<uint8_t, 16> uuidStringToByteArray(const std::string &uuidString) {
        std::array<uint8_t, 16> uuidBytes{};
        int index = 0;

        for (char c : uuidString) {
            if (c == '-')
                continue;

            uint8_t hex = 0;

            if (c >= '0' && c <= '9')
                hex = c - '0';
            else if (c >= 'a' && c <= 'f')
                hex = c - 'a' + 10;
            else if (c >= 'A' && c <= 'F')
                hex = c - 'A' + 10;

            if (index % 2 == 0)
                uuidBytes[index / 2] = hex << 4;
            else
                uuidBytes[index / 2] |= hex;
            ++index;
        }
        return uuidBytes;
    }

    std::string byteArrayToUuidString(const std::array<uint8_t, 16> &array) {
        std::ostringstream oss;

        for (std::size_t i = 0; i < array.size(); ++i) {
            if (i == 4 || i == 6 || i == 8 || i == 10)
                oss << '-';
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(array[i]);
        }
        return oss.str();
    }

    std::size_t uuidStringToNumeric(const std::string &uuidStr) {
        return std::hash<std::string>{}(uuidStr);
    }
}
