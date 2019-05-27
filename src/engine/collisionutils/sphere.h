#ifndef SPHERE_H
#define SPHERE_H
#include "object.h"

class Sphere : public Object
{
public:
    Sphere(glm::vec3 center, float radius);
    virtual ~Sphere() override {}
    virtual bool intersect(const glm::vec3 &pos, const glm::vec3 &dir, HitTest &result) const override;
    virtual void getSurfaceData(const glm::vec3 &p, glm::vec3 &n) const override;

    glm::vec3 center;
    float radius;
    float radius2;
};

#endif // SPHERE_H
