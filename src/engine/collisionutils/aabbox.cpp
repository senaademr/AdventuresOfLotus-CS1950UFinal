#include "aabbox.h"
#include "ray.h"
/**
 * Adopted from:
 * https://www.scratchapixel.com/code.php?id=10&origin=/lessons/3d-basic-rendering/&src=1
 * */
AABBox::AABBox(const glm::vec3 &b0, const glm::vec3 &b1)
{
    m_bounds[0] = b0;
    m_bounds[1] = b1;
}

AABBox::~AABBox()
{

}

bool AABBox::intersect(const Ray &r, float &t) const
{
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (m_bounds[r.sign[0]].x - r.orig.x) * r.invdir.x;
    tmax = (m_bounds[1-r.sign[0]].x - r.orig.x) * r.invdir.x;
    tymin = (m_bounds[r.sign[1]].y - r.orig.y) * r.invdir.y;
    tymax = (m_bounds[1-r.sign[1]].y - r.orig.y) * r.invdir.y;

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
    tmin = tymin;
    if (tymax < tmax)
    tmax = tymax;

    tzmin = (m_bounds[r.sign[2]].z - r.orig.z) * r.invdir.z;
    tzmax = (m_bounds[1-r.sign[2]].z - r.orig.z) * r.invdir.z;

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
    tmin = tzmin;
    if (tzmax < tmax)
    tmax = tzmax;

    t = tmin;

    if (t < 0) {
        t = tmax;
        if (t < 0) return false;
    }

    return true;
}
