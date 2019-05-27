#ifndef CIRCLEWEIGHTFUNCTION_H
#define CIRCLEWEIGHTFUNCTION_H

#include "engine/map_generation/weightfunction.h"

class CircleWeightFunction : public WeightFunction
{
public:
    CircleWeightFunction(glm::vec2 startingPoint, float radius, float distanceToOuterRadius);

    // MapNoise interface
public:
    float getWeight(glm::vec2 point) override;

private:
    glm::vec2 m_startingPoint;
    float m_radius;
    float m_distanceToOuterRadius;
};

#endif // CIRCLEWEIGHTFUNCTION_H
