/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** InputActionSystem
*/

#include "ecs.hpp"

#ifndef INPUTACTIONSYSTEM_HPP_
#define INPUTACTIONSYSTEM_HPP_

class InputActionSystem : public ecs::System {
    public:
        InputActionSystem();
        ~InputActionSystem() = default;

        virtual void onUpdate(float deltaTime) override;
        virtual void onStart() override;

    protected:
    private:
};

#endif /* !INPUTACTIONSYSTEM_HPP_ */
