#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "engine/components/tickable.h"
#include "engine/components/component.h"

class PhysicsComponent : public Component, public Tickable
{
public:
    PhysicsComponent();


    void tick(float seconds) override;

    void setVelocity(glm::vec3 new_velocity);

    void setXVelocity(float xVelocity);
    void setYVelocity(float yVelocity);
    void setZVelocity(float zVelocity);

    glm::vec3 getVelocity();
    void setGravity(bool hasGravity);

    void setAcceleration(glm::vec3 acceleration);
    glm::vec3 getAcceleration();

private:
    glm::vec3 m_velocity;
    glm::vec3 m_acceleration;
    bool m_hasGravity;
    float m_constant;
    bool m_hasTicked;
};

#endif // PHYSICSCOMPONENT_H
