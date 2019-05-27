#ifndef PLANE_H
#define PLANE_H
#include "object.h"

class Plane : public Object
{
public:
    Plane(glm::vec3 q, glm::vec3 normal);
    virtual ~Plane() override {}

    virtual bool intersect(const glm::vec3 &pos, const glm::vec3 &dir, HitTest &) const override;
    void getSurfaceData(const glm::vec3 &p, glm::vec3 &n) const override;
    bool isFrontFacingTo(const glm::vec3 &dir) const;
    float signedDistanceTo(const glm::vec3 &p) const;

    glm::vec3 q;
    glm::vec3 normal;
};

#endif // PLANE_H
