/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** WindowHitboxSystem
*/

#ifndef WINDOWHITBOXSYSTEM_HPP_
#define WINDOWHITBOXSYSTEM_HPP_

#include "ecs.hpp"

class WindowHitboxSystem : public ecs::System {
    public:
        WindowHitboxSystem();
        ~WindowHitboxSystem();

        void onUpdate(float deltaTime) override;

    protected:
    private:
};

#endif /* !WINDOWHITBOXSYSTEM_HPP_ */
