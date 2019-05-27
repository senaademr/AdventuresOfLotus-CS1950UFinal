#include "triangle.h"
#include "stdio.h"
#include <iostream>

Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) :
    Plane(v1, glm::cross(v2 - v1, v3 - v1))
{
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;
}

Triangle Triangle::scale(glm::vec3 basis){
    return Triangle(vertices[0]*basis, vertices[1]*basis, vertices[2]*basis);
}

bool Triangle::intersect(const glm::vec3 &pos, const glm::vec3 &dir, HitTest &result) const
{
    if (Plane::intersect(pos, dir, result) && inTriangle(result.hit)) {
        return true;
    }
    return false;
}

bool Triangle::inTriangle(const glm::vec3 &p) const
{
    // Point P (on plane) is inside triangle ABC iff P is on the left of all of the edges
    // A point is to the left of edge if the cross product is in the same direction as the triangle normal
    glm::vec3 crossAB = glm::cross(vertices[1] - vertices[0], p - vertices[0]); //ABxAP
    glm::vec3 crossBC = glm::cross(vertices[2] - vertices[1], p - vertices[1]); //BCxBP
    glm::vec3 crossCA = glm::cross(vertices[0] - vertices[2], p - vertices[2]); //CAxCP
    if (glm::dot(crossAB, normal) > 0 && glm::dot(crossBC, normal) > 0 && glm::dot(crossCA, normal) > 0) {
        return true;
    }
    return false;
}










