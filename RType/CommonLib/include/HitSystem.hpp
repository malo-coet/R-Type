/*
** EPITECH PROJECT, 2025
** RType-private
** File description:
** HitSystem
*/

#ifndef HITSYSTEM_HPP_
#define HITSYSTEM_HPP_

#include "ecs.hpp"

class HitSystem : public ecs::System {
    public:
        HitSystem();
        ~HitSystem();

        void onUpdate(float deltaTime) override;

    protected:
    private:
};

#endif /* !HITSYSTEM_HPP_ */
