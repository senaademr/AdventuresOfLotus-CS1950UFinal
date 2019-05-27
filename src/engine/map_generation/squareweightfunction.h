#ifndef SQUAREWEIGHTFUNCTION_H
#define SQUAREWEIGHTFUNCTION_H

#include "weightfunction.h"

class SquareWeightFunction : public WeightFunction
{
public:
    SquareWeightFunction(glm::vec2 startingPoint, float squareSize, float distanceToOuterSquare);

    // WeightFunction interface
public:
    float getWeight(glm::vec2 point);


private:
    glm::vec2 m_startingPoint;
    float m_squareSize;
    float m_distanceToOuterSquare;
};

#endif // SQUAREWEIGHTFUNCTION_H
