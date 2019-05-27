#include "circleweightfunction.h"

#include "engine/map_generation/valuenoise.h"

CircleWeightFunction::CircleWeightFunction(glm::vec2 startingPoint, float radius, float distanceToOuterRadius)
    : m_startingPoint(startingPoint),
      m_radius(radius),
      m_distanceToOuterRadius(distanceToOuterRadius)
{
}

float CircleWeightFunction::getWeight(glm::vec2 point){
    float distance = glm::distance(point, m_startingPoint);
    float outerRadius = m_radius + m_distanceToOuterRadius;
    if(distance < m_radius){
        return 1.f;
    }
    if(distance > outerRadius){
        return 0;
    }
    float t = (distance-m_radius)/m_distanceToOuterRadius;
    float result = ValueNoise::perlinInterpolation(1, 0, t);
    return result;

//    float fromRadius = 1+(distance - m_radius);
//    return m_strength/(fromRadius);
}
