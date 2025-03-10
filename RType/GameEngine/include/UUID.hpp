/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** UUID
*/

#ifndef UUID_HPP_
#define UUID_HPP_

#include <random>
#include <sstream>
#include <array>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

namespace uuid {
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::string generate_uuid_v4();

    std::array<uint8_t, 16> uuidStringToByteArray(const std::string &uuidString);

    std::string byteArrayToUuidString(const std::array<uint8_t, 16> &array);

    std::size_t uuidStringToNumeric(const std::string &uuidStr);
}

#endif /* !UUID_HPP_ */
