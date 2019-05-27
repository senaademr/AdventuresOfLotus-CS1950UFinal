#ifndef WEIGHTFUNCTION_H
#define WEIGHTFUNCTION_H

#include "glm/glm.hpp"

class WeightFunction
{
public:
    virtual float getWeight(glm::vec2 point) = 0;
};

#endif // WEIGHTFUNCTION_H
