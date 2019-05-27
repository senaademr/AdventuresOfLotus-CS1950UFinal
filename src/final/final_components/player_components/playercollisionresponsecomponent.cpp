#include "playercollisionresponsecomponent.h"

#include "engine/components/transformcomponent.h"
#include "engine/components/collisioncomponent.h"
#include "engine/components/physicscomponent.h"
#include "engine/basics/gameobject.h"
#include "playerabilitycomponent.h"


#include "playercontrolcomponent.h"
#include "final/final_components/enemy_components/enemyabilitycomponent.h"

PlayerCollisionResponseComponent::PlayerCollisionResponseComponent() :
    CollisionResponseComponent("player")
{

}

PlayerCollisionResponseComponent::~PlayerCollisionResponseComponent()
{

}

void PlayerCollisionResponseComponent::objectCollisionResponse(std::shared_ptr<CollisionResponseComponent> &other) {
    if (other->collisionResponseName() == "enemy") {
        if(other->getGameObject()->hasComponent<EnemyAbilityComponent>()){
            std::shared_ptr<EnemyAbilityComponent> enemyAbilityComponent
                    = other->getGameObject()->getComponent<EnemyAbilityComponent>();
            if(enemyAbilityComponent && !enemyAbilityComponent->isDead()){
                getGameObject()->getComponent<PlayerAbilityComponent>()->addToCurrentHealth(-enemyAbilityComponent->getDamage());
                sendFlying(other);
            }
        }
    }
}

void PlayerCollisionResponseComponent::sendFlying(std::shared_ptr<CollisionResponseComponent> &other){
//    std::cout << "send flying " << std::endl;
    glm::vec3 position = m_gameObject->getComponent<TransformComponent>()->getPosition();
    glm::vec3 enemyPosition = other->getGameObject()->getComponent<TransformComponent>()->getPosition();
    float flingSpeed = 20.f;
    glm::vec3 direction = flingSpeed* glm::normalize(position - enemyPosition);
    std::shared_ptr<PhysicsComponent> playerPhysics = m_gameObject->getComponent<PhysicsComponent>();

    playerPhysics->setXVelocity(direction.x);
    playerPhysics->setYVelocity(direction.y/5.f);
    playerPhysics->setZVelocity(direction.z);
}


void PlayerCollisionResponseComponent::continuousCollisionResponse() const{
    m_gameObject->getComponent<PlayerControlComponent>()->setCanJump();
}
