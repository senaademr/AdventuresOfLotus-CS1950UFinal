#include "dynamicmovecomponent.h"

#include "engine/basics/gameobject.h"
#include "engine/components/physicscomponent.h"

DynamicMoveComponent::DynamicMoveComponent(float frictionCoefficient, float accelConstant, float maxVelocity)
    :m_frictionCoefficient(frictionCoefficient),
    m_accelConstant(accelConstant),
    m_maxVelocity(maxVelocity),
    m_desiredDirection(glm::vec3(0))
{
}


void DynamicMoveComponent::tick(float seconds){

//    float accelConstant = 6.f;
    std::shared_ptr<PhysicsComponent> physicsComponent = m_gameObject->getComponent<PhysicsComponent>();
    glm::vec3 friction = physicsComponent->getVelocity() * glm::vec3(1, 0, 1);
    if(glm::length(friction) > 0){
        friction = glm::normalize(friction);
    }
    physicsComponent->setAcceleration(-m_frictionCoefficient*friction);

    glm::vec3 acceleration = m_accelConstant* m_desiredDirection;
    glm::vec3 oldVelocity = physicsComponent->getVelocity() * glm::vec3(1, 0, 1);
    glm::vec3 xz = oldVelocity + acceleration * seconds;
    if(glm::length(xz) > m_maxVelocity){
        float maxVel = std::max(m_maxVelocity, glm::length(oldVelocity));
        xz = maxVel * glm::normalize(xz);
    }
    physicsComponent->setXVelocity(xz.x);
    physicsComponent->setZVelocity(xz.z);

}


void DynamicMoveComponent::setMaxVelocity(float newMax){
    m_maxVelocity = newMax;
}

void DynamicMoveComponent::setDesiredDirection(glm::vec3 newDesiredDirection){
    if(glm::length(newDesiredDirection) > 0){
        m_desiredDirection = glm::normalize(newDesiredDirection);

    }
    else{
        m_desiredDirection = newDesiredDirection;

    }
}
