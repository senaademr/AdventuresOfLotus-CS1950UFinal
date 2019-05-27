#include "physicscomponent.h"

#include "engine/components/tickable.h"
#include "engine/basics/gameobject.h"
#include "engine/components/transformcomponent.h"

PhysicsComponent::PhysicsComponent()
    : Component (),
      Tickable(),
      m_velocity(glm::vec3(0, 0, 0)),
      m_acceleration(glm::vec3(0)),
      m_hasGravity(true),
      m_constant(-15.0f),
      m_hasTicked(false)
{
}

void PhysicsComponent::tick(float seconds){
    if(!m_hasTicked){
        m_hasTicked = true;
        return;
    }
    m_velocity += m_acceleration * seconds;
//    std::cout << "acceleration: " << m_acceleration << "  velocity: " << m_velocity << std::endl;
    if(m_hasGravity){
        setYVelocity(m_velocity.y + m_constant * seconds);
    }
//    transformComponent->translate(m_velocity * seconds);
}

void PhysicsComponent::setVelocity(glm::vec3 new_velocity){
    m_velocity = new_velocity;
}

void PhysicsComponent::setXVelocity(float xVelocity){
    m_velocity = glm::vec3(xVelocity, m_velocity.y, m_velocity.z);
}
void PhysicsComponent::setYVelocity(float yVelocity){
    m_velocity = glm::vec3(m_velocity.x, yVelocity, m_velocity.z);
}
void PhysicsComponent::setZVelocity(float zVelocity){
    m_velocity = glm::vec3(m_velocity.x, m_velocity.y, zVelocity);
}

glm::vec3 PhysicsComponent::getVelocity(){
    return m_velocity;
}

void PhysicsComponent::setGravity(bool hasGravity){
    m_hasGravity = hasGravity;
}


void PhysicsComponent::setAcceleration(glm::vec3 acceleration){
    m_acceleration =acceleration;
}

glm::vec3 PhysicsComponent::getAcceleration(){
    return m_acceleration;


}
