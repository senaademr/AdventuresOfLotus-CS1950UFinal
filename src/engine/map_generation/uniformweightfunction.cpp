#include "uniformweightfunction.h"

UniformWeightFunction::UniformWeightFunction(float strength)
    : m_strength(strength)
{
}

float UniformWeightFunction::getWeight(glm::vec2 point) {
    return m_strength;
}
