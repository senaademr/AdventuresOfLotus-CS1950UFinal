#include "linesegment.h"
#include "glm/ext.hpp"

LineSegment::LineSegment(glm::vec3 polarA, glm::vec3 polarB, float radius) :
    Object(),
    polarA(polarA),
    polarB(polarB),
    axisVector(polarB-polarA),
    radius(radius),
    radius2(radius*radius)
{

}

bool LineSegment::intersect(const glm::vec3 &pos, const glm::vec3 &dir, HitTest &result) const
{
    glm::vec3 proj;
    float t;
    if (intersectInfiniteLine(pos, dir, t) && inLineSegment(pos + t * dir, proj))
    {
        result.t = t;
        result.hit = proj;
        getSurfaceData(pos + t * dir, result.normal);
        return true;
    }
    return false;
}

void LineSegment::getSurfaceData(const glm::vec3 &p, glm::vec3 &n) const
{
    glm::vec3 proj;
    bool inLine = inLineSegment(p, proj);
    assert(inLine && p != proj);
    n = glm::normalize(p - proj);
}

bool LineSegment::intersectInfiniteLine(const glm::vec3 &pos, const glm::vec3 &dir, float &t) const
{
    glm::vec3 crossDir = glm::cross(dir, axisVector);
    glm::vec3 crossSide = glm::cross(pos - polarA, axisVector);
    float a = glm::length2(crossDir);
    float b = 2 * glm::dot(crossSide, crossDir);
    float c = glm::length2(crossSide) - glm::length2(axisVector)*radius2;
    float t0, t1;
    if (!solveQuadratic(a, b, c, t0, t1)) return false;

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
        t0 = t1; // if t0 is negative, let's use t1 instead
        if (t0 < 0) return false; // both t0 and t1 are negative
    }

    t = t0;
    return true;
}

bool LineSegment::inLineSegment(const glm::vec3 &p, glm::vec3 &projectionPoint) const
{
    float proj2 = glm::dot(p - polarA, axisVector);
    if (proj2 <= 0 || proj2 >= glm::length2(axisVector)) {
        return false;
    }
    projectionPoint = polarA + (proj2/glm::length2(axisVector)) * axisVector;
    return true;
}




