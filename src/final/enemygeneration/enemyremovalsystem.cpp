#include "enemyremovalsystem.h"

#include "engine/basics/gameobject.h"
#include "engine/basics/gameworld.h"
#include "engine/components/timeremovecomponent.h"
#include "engine/components/transformcomponent.h"
#include "final/mapgeneration/chunkloadingsystem.h"
#include "final/final_components/enemy_components/enemyabilitycomponent.h"
#include "final/final_components/player_components/playerlevelcomponent.h"

EnemyRemovalSystem::EnemyRemovalSystem(std::shared_ptr<GameWorld> gameWorld, std::shared_ptr<PlayerLevelComponent> playerLevelComponent)
    : TickSystem(TypeID::value<EnemyAbilityComponent>()),
      m_gameWorld(gameWorld),
      m_playerLevelComponent(playerLevelComponent)

{
}

void EnemyRemovalSystem::tick(float seconds){
    for(std::shared_ptr<Component> component : m_components){
        std::shared_ptr<EnemyAbilityComponent> enemyAbilityComponent
                = std::dynamic_pointer_cast<EnemyAbilityComponent>(component);
        if(enemyAbilityComponent){
            killEnemyIfDead(enemyAbilityComponent);
            removeEnemyIfFallenOffTerrain(enemyAbilityComponent);
        }
        else{
            std::cout << "bad component in enemy removal system" << std::endl;
        }
    }
}

void EnemyRemovalSystem::chunkRemoved(glm::ivec2 chunkCoordinate, float chunkSize){
//    std::cout << "Chunk removed: " << chunkCoordinate << std::endl;
    for(std::shared_ptr<Component> component : m_components){
        std::shared_ptr<TransformComponent> enemyTransform = component->getGameObject()->getComponent<TransformComponent>();
        glm::vec3 centerPosition = enemyTransform->getPosition();
        float xzSize = std::max(enemyTransform->getSize().x, enemyTransform->getSize().z);
        QList<glm::vec3> cornerOffsets = {glm::vec3(-1, 0, -1), glm::vec3(1, 0, -1), glm::vec3(-1, 0, 1), glm::vec3(1, 0, 1) };
        for(glm::vec3 cornerOffset : cornerOffsets){
            glm::vec3 position = centerPosition + (xzSize * cornerOffset);
            glm::ivec2 chunkCell = ChunkLoadingSystem::getCell(position, chunkSize);
            if(chunkCell.x == chunkCoordinate.x && chunkCell.y == chunkCoordinate.y){
//                std::cout << "removing enemy because chunk removed" << std::endl;
                m_gameWorld->removeObject(component->getGameObject());
                break;
            }
        }


    }
}

void EnemyRemovalSystem::killEnemyIfDead(std::shared_ptr<EnemyAbilityComponent> enemyAbilityComponent){
    if(enemyAbilityComponent->isDead() && !enemyAbilityComponent->getIsCounted()){
        enemyAbilityComponent->getGameObject()->getComponent<TimeRemoveComponent>()->setisTimerOn(true);
        enemyAbilityComponent->setIsCounted();
//        std::cout << "enemyDie" << std::endl;
        m_playerLevelComponent->addExperience(enemyAbilityComponent->getExperience());
    }

}

int EnemyRemovalSystem::getNumberEnemies(){
    return m_components.size();
}

void EnemyRemovalSystem::removeEnemyIfFallenOffTerrain(std::shared_ptr<EnemyAbilityComponent> enemyAbilityComponent){
    std::shared_ptr<TransformComponent> enemyTransform
            = enemyAbilityComponent->getGameObject()->getComponent<TransformComponent>();
    if(enemyTransform->getPosition().y < -100){
//        std::cout << "removing enemy because its too low" << std::endl;
        m_gameWorld->removeObject(enemyAbilityComponent->getGameObject());
    }
}

