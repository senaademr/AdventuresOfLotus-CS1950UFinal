#ifndef FLOOR_H
#define FLOOR_H
#include "interval.h"
#include "glm/glm.hpp"
struct Floor
{
    enum Type : char {Rectangle, Circle};
    Floor(float height) :
        height(height), hasBound(false){}
    Floor(Type type, float height, Interval xBound, Interval yBound) :
        type(type), height(height), hasBound(true), xBound(xBound), yBound(yBound){}
    Floor(Type type, float height, glm::vec2 center, float radius) :
        type(type), height(height), hasBound(true), center(center), radius(radius){}
    Type type;
    float height;
    bool hasBound;
    Interval xBound;
    Interval yBound;
    glm::vec2 center;
    float radius;
};
#endif // FLOOR_H
