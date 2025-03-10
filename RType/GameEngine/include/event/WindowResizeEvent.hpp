/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** WindowReszieEvent
*/

#ifndef WINDOWRESIZEEVENT_HPP_
#define WINDOWRESIZEEVENT_HPP_

#include "ecs.hpp"

struct WindowResizeEvent : public ecs::Event {
    int newWidth;
    int newHeight;

    WindowResizeEvent(int width, int height)
        : newWidth(width), newHeight(height) {}
};

#endif /* !WINDOWRESIZEEVENT_HPP_ */
