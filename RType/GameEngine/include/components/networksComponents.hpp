/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** networksComponents
*/

#ifndef NETWORKCOMPONENTS_HPP_
#define NETWORKCOMPONENTS_HPP_

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif
#include <enet/enet.h>

struct NetworkComponent {
    ENetPeer* peer;
    int networkId;
};

#endif /* !NETWORKSCOMPONENTS_HPP_ */
