#include "enemymovecomponent.h"

#include "engine/basics/gameobject.h"
#include "engine/components/physicscomponent.h"
#include "engine/components/transformcomponent.h"
#include "engine/components/animationcomponent.h"
#include "engine/navigation/navigationmesh.h"
#include "engine/util/ticktimer.h"
#include "engine/components/collisionresponsecomponent.h"
#include "enemycollisionresponsecomponent.h"
#include "engine/components/timeremovecomponent.h"

#include "final/final_components/enemy_components/enemyabilitycomponent.h"

EnemyMoveComponent::EnemyMoveComponent(std::shared_ptr<TransformComponent> playerTransform, std::shared_ptr<NavigationMesh> navmesh, std::__cxx11::string enemyName)
    : m_playerTransform(playerTransform),
      m_navmesh(navmesh),
      m_enemyType(enemyName),
      m_tickTimer(nullptr)
{
    m_tickTimer = std::make_shared<TickTimer>(.02f, true);
    loadAnimationIndices();
}


void EnemyMoveComponent::tick(float seconds){
    std::shared_ptr<EnemyAbilityComponent> enemyAbilityComponent = m_gameObject->getComponent<EnemyAbilityComponent>();

    if(m_tickTimer->isTime(seconds)){
//        std::shared_ptr<EnemyCollisionResponseComponent> colResponse = std::dynamic_pointer_cast<EnemyCollisionResponseComponent>(getGameObject()->getComponent<CollisionResponseComponent>());
        if(enemyAbilityComponent->isDead()){
            die();
            return;
        }
        float dist = glm::distance(m_gameObject->getComponent<TransformComponent>()->getPosition(), m_playerTransform->getPosition());
        float attackDistance = 4.f;
        std::shared_ptr<PhysicsComponent> physics = m_gameObject->getComponent<PhysicsComponent>();
        if( dist <= attackDistance){
            attack();
        }
        else if (dist > attackDistance && dist <= 15.f){
            glm::vec3 direction = getDirectionOfPathTowardPoint(m_playerTransform->getPosition());
            if(direction.x != 0 || direction.z != 0){
                m_gameObject->getComponent<AnimationComponent>()->changeAnimation(m_indices.y);
                float cosAngle = glm::dot(direction, glm::vec3(0.f, 0.f, 1.f));
                float angle = glm::acos(cosAngle);
                if(direction.x >0 ){
                    m_gameObject->getComponent<TransformComponent>()->setRotation(glm::radians(180.f) + angle, glm::vec3(0, 1, 0));
                }
                else{
                    m_gameObject->getComponent<TransformComponent>()->setRotation(glm::radians(180.f)-angle, glm::vec3(0, 1, 0));
                }
                float velocity = enemyAbilityComponent->getMovementSpeed();
                physics->setXVelocity(direction.x * velocity);
                physics->setZVelocity(direction.z * velocity);
            } else {
                m_gameObject->getComponent<AnimationComponent>()->changeAnimation(m_indices.x);
                physics->setXVelocity(0);
                physics->setZVelocity(0);
            }
        } else {
            m_gameObject->getComponent<AnimationComponent>()->changeAnimation(m_indices.x);
            physics->setXVelocity(0);
            physics->setZVelocity(0);
        }
    }
}

void EnemyMoveComponent::die(){
    m_gameObject->getComponent<AnimationComponent>()->changeAnimation(m_indices.w);
    std::shared_ptr<PhysicsComponent> physics = m_gameObject->getComponent<PhysicsComponent>();
    physics->setXVelocity(0);
    physics->setZVelocity(0);
    return;
}

glm::vec3 EnemyMoveComponent::getDirectionOfPathTowardPoint(glm::vec3 point){
    QList<glm::vec3> pathToPlayer = m_navmesh->navigate(m_gameObject->getComponent<TransformComponent>()->getPosition(), point);

    if(pathToPlayer.size() >= 2){
        return glm::normalize((pathToPlayer.at(1)-pathToPlayer.at(0)) * glm::vec3(1, 0, 1));
    }
    if(pathToPlayer.size() == 0){
//        std::cout << "cannot find path to player" << std::endl;
        return glm::vec3(0);
    }
    return glm::vec3(0);
}

void EnemyMoveComponent::attack(){
    float velocity = m_gameObject->getComponent<EnemyAbilityComponent>()->getMovementSpeed();
    glm::vec3 direction = glm::normalize(m_playerTransform->getPosition() - m_gameObject->getComponent<TransformComponent>()->getPosition());
    if(direction.x != 0 || direction.z != 0){
        float cosAngle = glm::dot(direction, glm::vec3(0.f, 0.f, 1.f));
        float angle = glm::acos(cosAngle);
        if(direction.x >0 ){
            m_gameObject->getComponent<TransformComponent>()->setRotation(glm::radians(180.f) + angle, glm::vec3(0, 1, 0));
        }
        else{
            m_gameObject->getComponent<TransformComponent>()->setRotation(glm::radians(180.f)-angle, glm::vec3(0, 1, 0));
        }
        std::shared_ptr<PhysicsComponent> physics = m_gameObject->getComponent<PhysicsComponent>();
        physics->setXVelocity(direction.x * velocity);
        physics->setZVelocity(direction.z * velocity);
    }
    m_gameObject->getComponent<AnimationComponent>()->changeAnimation(m_indices.z);
}

void EnemyMoveComponent::loadAnimationIndices(){
    glm::vec4 indices = glm::vec4(0);
    if(!m_enemyType.compare("spider")){
        indices.x = 14;
        indices.y = 11;
        indices.z = 2;
        indices.w = 1;
    }
    else if(!m_enemyType.compare("magma")){
        indices.x = 6;
        indices.y = 11;
        indices.z = 9;
        indices.w = 3;
    }
    else if(!m_enemyType.compare("space")){
        indices.x = 7;
        indices.y = 9;
        indices.z = 2;
        indices.w = 5;
    }
    m_indices = indices;
}
