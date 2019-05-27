#ifndef UNIFORMWEIGHTFUNCTION_H
#define UNIFORMWEIGHTFUNCTION_H

#include "engine/map_generation/weightfunction.h"

class UniformWeightFunction : public WeightFunction
{
public:
    UniformWeightFunction(float strength);

    // MapNoise interface
public:
    float getWeight(glm::vec2 point) override;

private:
    float m_strength;
};

#endif // UNIFORMWEIGHTFUNCTION_H
