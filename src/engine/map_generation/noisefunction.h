#ifndef NOISEFUNCTION_H
#define NOISEFUNCTION_H

#include "glm/glm.hpp"

class NoiseFunction
{
public:
    virtual float interpolatedNoise(glm::vec2 point)  = 0;
    virtual glm::vec3 interpolatedNoiseToVec(const glm::vec2 &vec) = 0;
};

#endif // NOISEFUNCTION_H
