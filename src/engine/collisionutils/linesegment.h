#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include "object.h"

// LineSegment is a line made of not distorted cylinder
class LineSegment : public Object
{
public:
    LineSegment(glm::vec3 polarA, glm::vec3 polarB, float radius); // radius = half of the width of the line
    ~LineSegment() override {}
    bool intersect(const glm::vec3 &pos, const glm::vec3 &dir, HitTest &result) const override;
    void getSurfaceData(const glm::vec3 &p, glm::vec3 &n) const override;
    bool intersectInfiniteLine(const glm::vec3 &pos, const glm::vec3 &dir, float &t) const;
    bool inLineSegment(const glm::vec3 &p, glm::vec3 &projectionPoint) const;

    glm::vec3 polarA;
    glm::vec3 polarB;
    glm::vec3 axisVector;
    float radius;
    float radius2;
};

#endif // LINESEGMENT_H
