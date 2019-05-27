#ifndef DYNAMICMOVECOMPONENT_H
#define DYNAMICMOVECOMPONENT_H

#include "engine/components/component.h"
#include "engine/components/tickable.h"

class DynamicMoveComponent : public Component, public Tickable
{
public:
    DynamicMoveComponent(float frictionCoefficient, float accelConstant, float maxVelocity);

    // Tickable interface
public:
    void tick(float seconds);

    void setMaxVelocity(float newMax);
    void setDesiredDirection(glm::vec3 newDesiredDirection);

private:
    float m_frictionCoefficient;
    float m_accelConstant;
    float m_maxVelocity;
    glm::vec3 m_desiredDirection;

};

#endif // DYNAMICMOVECOMPONENT_H
