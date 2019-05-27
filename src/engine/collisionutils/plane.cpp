#include "plane.h"
#include <iostream>

Plane::Plane(glm::vec3 q, glm::vec3 normal) :
    Object(),
    q(q),
    normal(glm::normalize(normal))
{

}

/*
 * Only cares about intersection on the same side of plane normal
*/
bool Plane::intersect(const glm::vec3 &pos, const glm::vec3 &dir, HitTest &result) const
{
    float denom = glm::dot(normal, dir);
    if (denom == 0.f) { // parallel to plane
        return false;
    }
    float t = glm::dot(q - pos, normal) / denom;
    if (t >= 0) {
        result.t = t;
        result.hit = pos + result.t * dir;
        getSurfaceData(result.hit, result.normal);
        return true;
    }
    return false;
}

void Plane::getSurfaceData(const glm::vec3 &p, glm::vec3 &n) const
{
    n = normal;
}

bool Plane::isFrontFacingTo(const glm::vec3 &dir) const {
    return glm::dot(normal, dir) <= 0.f;
}

float Plane::signedDistanceTo(const glm::vec3 &p) const {
    return glm::dot(p-q, normal);
}
