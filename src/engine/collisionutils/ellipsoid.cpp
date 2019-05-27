#include "ellipsoid.h"
#include "sphere.h"

Ellipsoid::Ellipsoid(glm::vec3 center, float rx, float ry, float rz) : Ellipsoid(center, glm::vec3(rx, ry, rz))
{
}

Ellipsoid::Ellipsoid(glm::vec3 center, glm::vec3 radius) :
    Object(),
    center(center), radius(radius),
    m_unitSphereSpaceMatrix(glm::mat3(1.f/radius.x, 0.f, 0.f,
                                      0.f, 1.f/radius.y, 0.f,
                                      0.f, 0.f, 1.f/radius.z))
{
}

bool Ellipsoid::intersect(const glm::vec3 &pos, const glm::vec3 &dir, HitTest &result) const
{
    // transit positions to unit sphere space
    glm::vec3 centerUnit, posUnit, dirUnit;
    unitSphereSpace(center, centerUnit);
    unitSphereSpace(pos, posUnit);
    unitSphereSpace(dir, dirUnit);

    if (Sphere(centerUnit, 1.f).intersect(posUnit, dirUnit, result)) {
        result.hit *= radius; // convert back to world space
        getSurfaceData(result.hit, result.normal); // update normal
        return true;
    }
    return false;
}

void Ellipsoid::getSurfaceData(const glm::vec3 &p, glm::vec3 &n) const
{
    glm::vec3 pOrigCenter = p - center;
    n = glm::normalize(2.f * glm::vec3(pOrigCenter.x/(radius.x*radius.x), pOrigCenter.y/(radius.y*radius.y), pOrigCenter.z/(radius.z*radius.z)));
}

void Ellipsoid::unitSphereSpace(const glm::vec3 &p, glm::vec3 &pOut) const
{
    pOut = m_unitSphereSpaceMatrix * p;
}
