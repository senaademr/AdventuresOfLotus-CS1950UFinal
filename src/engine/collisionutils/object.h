#ifndef OBJECT_H
#define OBJECT_H
#include "hittest.h"

class Object
{
public:
    Object();
    virtual ~Object() {}
    // Ray intersect
    virtual bool intersect(const glm::vec3 &, const glm::vec3 &, HitTest &) const = 0;
    // Get information such as normal
    virtual void getSurfaceData(const glm::vec3 &, glm::vec3 &) const = 0;
    bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) const;
};

#endif // OBJECT_H
