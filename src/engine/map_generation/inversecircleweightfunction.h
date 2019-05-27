#ifndef INVERSECIRCLEWEIGHTFUNCTION_H
#define INVERSECIRCLEWEIGHTFUNCTION_H

#include "engine/map_generation/weightfunction.h"

class InverseCircleWeightFunction : public WeightFunction
{
public:
    InverseCircleWeightFunction(glm::vec2 startingPoint, float radius, float distanceToOuterRadius);

    // MapNoise interface
public:
    float getWeight(glm::vec2 point) override;

private:
    glm::vec2 m_startingPoint;
    float m_radius;
    float m_distanceToOuterRadius;
};

#endif // INVERSECIRCLEWEIGHTFUNCTION_H
