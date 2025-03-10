/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** ParalaxResetSystem
*/

#ifndef PARALAXRESETSYSTEM_HPP_
#define PARALAXRESETSYSTEM_HPP_

#include "ecs.hpp"

class ParalaxResetSystem : public ecs::System {
    public:
        ParalaxResetSystem();
        ~ParalaxResetSystem();

        void onUpdate(float deltaTime) override;

    protected:
    private:
};

#endif /* !PARALAXRESETSYSTEM_HPP_ */
