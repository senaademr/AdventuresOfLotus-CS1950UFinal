#ifndef ENEMYREMOVALSYSTEM_H
#define ENEMYREMOVALSYSTEM_H

#include "engine/systems/ticksystem.h"

class GameWorld;
class EnemyAbilityComponent;
class PlayerLevelComponent;

class EnemyRemovalSystem : public TickSystem
{
public:
    EnemyRemovalSystem(std::shared_ptr<GameWorld> gameWorld, std::shared_ptr<PlayerLevelComponent> playerLevelComponent);

    // TickSystem interface
public:
    void tick(float seconds) override;

    void chunkRemoved(glm::ivec2 chunkCoordinate, float chunkSize);
    int getNumberEnemies();

private:
    void killEnemyIfDead(std::shared_ptr<EnemyAbilityComponent> enemyAbilityComponent);
    void removeEnemyIfFallenOffTerrain(std::shared_ptr<EnemyAbilityComponent> enemyAbilityComponent);

private:
    std::shared_ptr<GameWorld> m_gameWorld;
    std::shared_ptr<PlayerLevelComponent> m_playerLevelComponent;
};

#endif // ENEMYREMOVALSYSTEM_H
