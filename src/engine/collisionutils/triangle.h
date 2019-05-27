#ifndef TRIANGLE_H
#define TRIANGLE_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include "plane.h"

class Triangle : public Plane
{
public:
    Triangle();
    // Vertices must be in CCW order
    Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    Triangle scale(glm::vec3 basis);

    glm::vec3 vertices[3];

    bool intersect(const glm::vec3 &pos, const glm::vec3 &dir, HitTest &result) const override;
    bool inTriangle(const glm::vec3 &p) const;
};

#endif // TRIANGLE_H
