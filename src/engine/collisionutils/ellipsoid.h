#ifndef ELLIPSOID_H
#define ELLIPSOID_H
#include "object.h"

class Ellipsoid : public Object
{
public:
    Ellipsoid(glm::vec3 center, float rx, float ry, float rz);
    Ellipsoid(glm::vec3 center, glm::vec3 radius);
    ~Ellipsoid() override {}
    bool intersect(const glm::vec3 &pos, const glm::vec3 &dir, HitTest &result) const override;
    void getSurfaceData(const glm::vec3 &p, glm::vec3 &n) const override;
    void unitSphereSpace(const glm::vec3 &p, glm::vec3 &pOut) const;

    glm::vec3 center;
    glm::vec3 radius;

private:
    glm::mat3 m_unitSphereSpaceMatrix;
};

#endif // ELLIPSOID_H
