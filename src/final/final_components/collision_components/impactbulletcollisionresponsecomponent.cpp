#include "impactbulletcollisionresponsecomponent.h"

#include "engine/basics/gameobject.h"
#include "engine/components/physicscomponent.h"

ImpactBulletCollisionResponseComponent::ImpactBulletCollisionResponseComponent(std::shared_ptr<GameWorld> gameWorld, float damage, float impactPower)
    : BulletCollisionResponseComponent(gameWorld, damage),
      m_impactPower(impactPower)
{
}


void ImpactBulletCollisionResponseComponent::objectCollisionResponse(std::shared_ptr<CollisionResponseComponent> &other){
    BulletCollisionResponseComponent::objectCollisionResponse(other);
    std::cout << "impact" << std::endl;

    if(other->collisionResponseName().compare("enemy") == 0){
        glm::vec3 impactDirection = glm::normalize(m_gameObject->getComponent<PhysicsComponent>()->getVelocity());
//        other->collideContinuous(glm::normalize(impactDirection) * m_impactPower);
//        std::cout << "impact!" << std::endl;
        other->getGameObject()->getComponent<PhysicsComponent>()->setVelocity(impactDirection *m_impactPower );
    }
}
