#include "inversecircleweightfunction.h"

#include "engine/map_generation/valuenoise.h"

InverseCircleWeightFunction::InverseCircleWeightFunction(glm::vec2 startingPoint, float radius, float distanceToOuterRadius)
    : m_startingPoint(startingPoint),
      m_radius(radius),
      m_distanceToOuterRadius(distanceToOuterRadius)
{
}

float InverseCircleWeightFunction::getWeight(glm::vec2 point){
    float distance = glm::distance(point, m_startingPoint);
    float outerRadius = m_radius + m_distanceToOuterRadius;
    if(distance < m_radius){
        return 0.f;
    }
    if(distance > outerRadius){
        return 1;
    }
    float t = (distance-m_radius)/m_distanceToOuterRadius;
    float result = ValueNoise::perlinInterpolation(0, 1, t);
    return result;

//    float fromRadius = 1+(distance - m_radius);
//    return m_strength/(fromRadius);
}
