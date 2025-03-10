#include "CommonLib/factory/EntityFactory.hpp"

void shootGunOne(ecs::Registry &reg, ecs::Entity &ent)
{
    position pos = ent.getComponent<position>();
    EntityFactory::createProjectile(reg, pos.x, pos.y, 300.0f, 0.0f);
}

void shootGunOneEnemy(ecs::Registry &reg, ecs::Entity &ent)
{
    position pos = ent.getComponent<position>();
    EntityFactory::createProjectileEnemy(reg, pos.x, pos.y, -300.0f, 0.0f);
}

void shootGunTwoEnemy(ecs::Registry &reg, ecs::Entity &ent)
{
    position pos = ent.getComponent<position>();
    EntityFactory::createProjectileEnemy(reg, pos.x - 40, pos.y + 30, -300.0f, 0.0f);
    EntityFactory::createProjectileEnemy(reg, pos.x - 40, pos.y + 30, -300.0f, -100.0f);
    EntityFactory::createProjectileEnemy(reg, pos.x - 40, pos.y + 30, -300.0f, 100.0f);
    EntityFactory::createProjectileEnemy(reg, pos.x, pos.y + 100, -300.0f, 0.0f);
    EntityFactory::createProjectileEnemy(reg, pos.x + 10, pos.y + 120, -300.0f, 0.0f);
}

void shootGunThreeEnemy(ecs::Registry &reg, ecs::Entity &ent)
{
    position pos = ent.getComponent<position>();
    EntityFactory::createProjectileEnemy(reg, pos.x + 250, pos.y + 300, -300.0f, 0.0f);
    EntityFactory::createProjectileEnemy(reg, pos.x + 250, pos.y + 300, -300.0f, -100.0f);
    EntityFactory::createProjectileEnemy(reg, pos.x + 250, pos.y + 300, -300.0f, 100.0f);
    EntityFactory::createProjectileEnemy(reg, pos.x + 250, pos.y + 300, -300.0f, -200.0f);
    EntityFactory::createProjectileEnemy(reg, pos.x + 250, pos.y + 300, -300.0f, 200.0f);
}
