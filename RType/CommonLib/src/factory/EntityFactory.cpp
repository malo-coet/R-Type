#include "CommonLib/factory/EntityFactory.hpp"
#include "CommonLib/FactionComponent.hpp"
#include "CommonLib/HitboxComponent.hpp"
#include "CommonLib/entitycomponents.hpp"
#include "components/graphicsComponents.hpp"
#include "UUID.hpp"

ecs::Entity EntityFactory::createPlayer(ecs::Registry& registry, float x, float y, float vx, float vy) {
    ecs::Entity player = registry.spawnEntity(uuid::generate_uuid_v4());
    player.addComponent<position>({x, y});
    player.addComponent<velocity>({vx, vy});
    player.addComponent<typeComponent>({EntityType::PLAYER});
    player.addComponent<Action>({shootGunOne});
    player.addComponent<Faction>({1});
    player.addComponent<Health>({10, 10});
    player.addComponent<Hitbox>({106, 42}); // scale is taken in account
    return player;
}

ecs::Entity EntityFactory::creatBackground(ecs::Registry& registry, float x, float y) {
    ecs::Entity paralax = registry.spawnEntity();
    paralax.addComponent<position>({x, y});
    paralax.addComponent<typeComponent>({EntityType::BACKGROUND});
    paralax.addComponent<RenderableComponent>({EntityType::BACKGROUND});
    paralax.addComponent<AudioComponent>({AudioComponent::Type::Music, "music", true, SDL_MIX_MAXVOLUME / 2});
    return paralax;
}

ecs::Entity EntityFactory::createParalax(ecs::Registry& registry, float x, float y, float vx, float vy) {
    ecs::Entity paralax = registry.spawnEntity();
    paralax.addComponent<position>({x, y});
    paralax.addComponent<velocity>({vx, vy});
    paralax.addComponent<FactionParalax>({true});
    paralax.addComponent<typeComponent>({EntityType::PARALAX});
    paralax.addComponent<RenderableComponent>({EntityType::PARALAX});
    return paralax;
}

ecs::Entity EntityFactory::createParalaxTwo(ecs::Registry& registry, float x, float y, float vx, float vy) {
    ecs::Entity paralax = registry.spawnEntity();
    paralax.addComponent<position>({x, y});
    paralax.addComponent<velocity>({vx, vy});
    paralax.addComponent<FactionParalax>({true});
    paralax.addComponent<typeComponent>({EntityType::PARALAX_TWO});
    paralax.addComponent<RenderableComponent>({EntityType::PARALAX_TWO});
    return paralax;
}

ecs::Entity EntityFactory::createEnemy(ecs::Registry& registry, float x, float y, float vx, float vy) {
    ecs::Entity enemy = registry.spawnEntity(uuid::generate_uuid_v4());
    enemy.addComponent<position>({x, y});
    enemy.addComponent<velocity>({vx, vy});
    enemy.addComponent<typeComponent>({EntityType::ENEMY});
    enemy.addComponent<Action>({shootGunOneEnemy, 200.0f});
    enemy.addComponent<Health>({1, 1});
    enemy.addComponent<Faction>({2});
    enemy.addComponent<FactionEnemy>({});
    enemy.addComponent<Hitbox>({69, 76});
    return enemy;
}

ecs::Entity EntityFactory::createEnemyMed(ecs::Registry& registry, float x, float y, float vx, float vy) {
    ecs::Entity enemy = registry.spawnEntity(uuid::generate_uuid_v4());
    enemy.addComponent<position>({x, y});
    enemy.addComponent<velocity>({vx, vy});
    enemy.addComponent<typeComponent>({EntityType::ENEMY_MED});
    enemy.addComponent<Action>({shootGunTwoEnemy, 200.0f});
    enemy.addComponent<Health>({5, 5});
    enemy.addComponent<Faction>({2});
    enemy.addComponent<FactionEnemy>({});
    enemy.addComponent<Hitbox>({386, 326});
    return enemy;
}

ecs::Entity EntityFactory::createEnemyBig(ecs::Registry& registry, float x, float y, float vx, float vy) {
    ecs::Entity enemy = registry.spawnEntity(uuid::generate_uuid_v4());
    enemy.addComponent<position>({700, 70});
    enemy.addComponent<velocity>({vx, vy});
    enemy.addComponent<typeComponent>({EntityType::ENEMY_BIG});
    enemy.addComponent<Action>({shootGunThreeEnemy, 200.0f});
    enemy.addComponent<Health>({10, 10});
    enemy.addComponent<Faction>({2});
    enemy.addComponent<FactionEnemy>({});
    enemy.addComponent<Hitbox>({380, 488});
    return enemy;
}

ecs::Entity EntityFactory::createProjectile(ecs::Registry& registry, float x, float y, float vx, float vy) {
    ecs::Entity projectile = registry.spawnEntity(uuid::generate_uuid_v4());
    projectile.addComponent<position>({x, y});
    projectile.addComponent<velocity>({vx, vy});
    projectile.addComponent<typeComponent>({EntityType::PROJECTILE});
    projectile.addComponent<Faction>({1});
    projectile.addComponent<Health>({1, 1});
    projectile.addComponent<Hitbox>({51, 26});
    return projectile;
}

ecs::Entity EntityFactory::createProjectileEnemy(ecs::Registry& registry, float x, float y, float vx, float vy) {
    ecs::Entity projectile = registry.spawnEntity(uuid::generate_uuid_v4());
    projectile.addComponent<position>({x, y});
    projectile.addComponent<velocity>({vx, vy});
    projectile.addComponent<typeComponent>({EntityType::ENEMY_PROJECTILE});
    projectile.addComponent<Faction>({2});
    projectile.addComponent<Health>({1, 1});
    projectile.addComponent<Hitbox>({51, 51});
    return projectile;
}

ecs::Entity EntityFactory::createProjectileAsteroid(ecs::Registry& registry, float x, float y, float vx, float vy) {
    ecs::Entity asteroid = registry.spawnEntity(uuid::generate_uuid_v4());
    asteroid.addComponent<position>({x, y});
    asteroid.addComponent<velocity>({vx, vy});
    asteroid.addComponent<typeComponent>({EntityType::ASTEROID});
    asteroid.addComponent<Faction>({2});
    asteroid.addComponent<Health>({1, 1});
    asteroid.addComponent<RenderableComponent>({EntityType::ASTEROID});
    asteroid.addComponent<Hitbox>({160, 135});
    return asteroid;
}

ecs::Entity EntityFactory::createEntityFromState(ecs::Registry& registry, const EntityState& state) {
    ecs::Entity entity = registry.spawnEntity(uuid::byteArrayToUuidString(state.entityId));
    entity.addComponent<position>({state.x, state.y});
    entity.addComponent<velocity>({state.dx, state.dy});
    entity.addComponent<typeComponent>({static_cast<EntityType>(state.entityType)});
    entity.addComponent<RenderableComponent>({state.entityType});
    switch (static_cast<EntityType>(state.entityType)) {
    case EntityType::PLAYER :
        entity.addComponent<Faction>({1});
        entity.addComponent<Health>({10, 10});
        entity.addComponent<Hitbox>({106, 42});
        break;
    case  EntityType::PROJECTILE :
        entity.addComponent<Faction>({1});
        entity.addComponent<Health>({1, 1});
        entity.addComponent<Hitbox>({51, 26});
        entity.addComponent<AudioComponent>({AudioComponent::Type::SoundEffect, "laser", false, SDL_MIX_MAXVOLUME});
        break;
    case EntityType::ENEMY :
        entity.addComponent<Faction>({2});
        entity.addComponent<Health>({1, 1});
        entity.addComponent<Hitbox>({69, 76});
        break;
    case EntityType::ENEMY_MED :
        entity.addComponent<Faction>({2});
        entity.addComponent<Health>({5, 5});
        entity.addComponent<Hitbox>({386, 326});
        break;
    case EntityType::ENEMY_BIG :
        entity.addComponent<Faction>({2});
        entity.addComponent<Health>({10, 10});
        entity.addComponent<Hitbox>({380, 488});
        entity.addComponent<AudioComponent>({AudioComponent::Type::SoundEffect, "boss", false, SDL_MIX_MAXVOLUME});
        break;
    case EntityType::ENEMY_PROJECTILE :
        entity.addComponent<Faction>({2});
        entity.addComponent<Health>({1, 1});
        entity.addComponent<Hitbox>({51, 51});
        break;
    case EntityType::ASTEROID :
        entity.addComponent<Faction>({2});
        entity.addComponent<Health>({1, 1});
        entity.addComponent<Hitbox>({160, 135});
        break;
    default:
        break;
    }
    return entity;
}
