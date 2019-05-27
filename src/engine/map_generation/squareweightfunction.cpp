#include "squareweightfunction.h"

#include <math.h>
#include "engine/map_generation/valuenoise.h"

SquareWeightFunction::SquareWeightFunction(glm::vec2 startingPoint, float squareSize, float distanceToOuterSquare)
    : m_startingPoint(startingPoint),
      m_squareSize(squareSize),
      m_distanceToOuterSquare(distanceToOuterSquare)
{
}


float SquareWeightFunction::getWeight(glm::vec2 point){
    float distance = std::max(std::abs(point.x- m_startingPoint.x), std::abs(point.y - m_startingPoint.y));
    float outerRadius = m_squareSize + m_distanceToOuterSquare;
    if(distance < m_squareSize){
        return 1.f;
    }
    if(distance > outerRadius){
        return 0;
    }
    float t = (distance-m_squareSize)/m_distanceToOuterSquare;
    float result = ValueNoise::perlinInterpolation(1, 0, t);
    return result;
}

