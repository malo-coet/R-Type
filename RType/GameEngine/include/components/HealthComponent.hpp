#ifndef HEALTH_COMPONENT_HPP
#define HEALTH_COMPONENT_HPP

struct HealthComponent {
    int hp;
    int maxHp;

    HealthComponent(int hp = 100, int maxHp = 100)
        : hp(hp), maxHp(maxHp) {}
};

#endif
