#include "sphere.h"
#include <memory>

Sphere::Sphere(glm::vec3 center, float radius) :
    Object(),
    center(center),
    radius(radius),
    radius2(radius * radius)
{

}

bool Sphere::intersect(const glm::vec3 &pos, const glm::vec3 &dir, HitTest &result) const
{
    glm::vec3 L = pos - center;
    float a = glm::dot(dir, dir);
    float b = 2 * glm::dot(dir, L);
    float c = glm::dot(L, L) - radius2;
    float t0, t1;
    if (!solveQuadratic(a, b, c, t0, t1)) return false;

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
        t0 = t1; // if t0 is negative, let's use t1 instead
        if (t0 < 0) return false; // both t0 and t1 are negative
    }

    result.t = t0;
    result.hit = pos + result.t * dir;
    getSurfaceData(result.hit, result.normal);

    return true;
}

void Sphere::getSurfaceData(const glm::vec3 &p, glm::vec3 &n) const
{
    n = glm::normalize(p - center);
}
