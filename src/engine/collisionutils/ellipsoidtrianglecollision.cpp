#include "ellipsoidtrianglecollision.h"
#include "triangle.h"
#include "ellipsoid.h"
#include "linesegment.h"
#include "sphere.h"
#include <iostream>

EllipsoidTriangleCollision::EllipsoidTriangleCollision(glm::vec3 radius) :
    ellipsoid(std::make_shared<Ellipsoid>(glm::vec3(0.f), radius))
{
}

void EllipsoidTriangleCollision::updateTriangles(const QList<std::shared_ptr<Triangle>> &triangles)
{
    glm::vec3 v1, v2, v3;
    m_triangles = QList<std::shared_ptr<Triangle>>();
    for (const std::shared_ptr<Triangle> &triangle : triangles) {
        ellipsoid->unitSphereSpace(triangle->vertices[0], v1);
        ellipsoid->unitSphereSpace(triangle->vertices[1], v2);
        ellipsoid->unitSphereSpace(triangle->vertices[2], v3);
        m_triangles.append(std::make_shared<Triangle>(v1, v2, v3));
    }
}

/**
 * Find the closest collision of the sphere along its direction of motion.
 * In class, we covered how to detect a collision of a sphere that moves
 * from a start position to an end position with each part of a triangle.
 * You'll basically do this with the sphere and each triangle.
 *
 * 1) Get the start and end position of the ellipsoid for the current tick
 * 2) Transform start and end position into unit sphere space
 *    (i.e. divide each component of vertex by ellipsoid radius in that dimension)
 * 3) Iterate over each triangle in the world, and transform it's vertices into sphere space
 *    (i.e. divide each component of vertex by ellipsoid radius in that dimension)
 * 4) Use start and end position from step 2 to check for collision of sphere with each part of triangle (interior, edge, vertex)
 * 5) Return min t value which satisfies 0 < t < 1 from all collisions
 * 6) Move the ellipsoid to the new position start + t * (start - end)
 */
bool EllipsoidTriangleCollision::continuousCollisionTest(const glm::vec3 &start, const glm::vec3 &end, HitTest &result) const {
    glm::vec3 a, b;
    ellipsoid->unitSphereSpace(start, a);
    ellipsoid->unitSphereSpace(end, b);
    return intersectUnitSphereSpace(a, b-a, result);
}

bool EllipsoidTriangleCollision::intersectUnitSphereSpace(const glm::vec3 &pos,
                                                          const glm::vec3 &vel,
                                                          HitTest &result) const {
    bool intersect = false;
    HitTest temp_result;
    result.t = 1.f;
    for (const std::shared_ptr<Triangle> &triangle : m_triangles) {
        if (sphereTriangle(pos, vel, triangle, temp_result) && temp_result.t < result.t) {
            result = temp_result;
            intersect = true;
        }
    }
    return intersect;
}

glm::vec3 EllipsoidTriangleCollision::continuousCollisionResponse(const glm::vec3 &start, const glm::vec3 &end, bool &collided) const {
    glm::vec3 a, b, dest;
    ellipsoid->unitSphereSpace(start, a);
    ellipsoid->unitSphereSpace(end, b);
    int collisionRecursionDepth = 0;
    dest = collideUnitSphereSpace(a, b-a, collisionRecursionDepth);
    if (collisionRecursionDepth > 0) {
        collided = true;
    }
    return dest * ellipsoid->radius; // back to world space
}

glm::vec3 EllipsoidTriangleCollision::collideUnitSphereSpace(const glm::vec3 &pos,
                                                             const glm::vec3 &vel,
                                                             int &collisionRecursionDepth) const {
    //std::cout << "collistion recursion depth=" << collisionRecursionDepth << std::endl;
    if (collisionRecursionDepth > 3) {
        // no need to worry
        return pos;
    }

    HitTest result;
    if (!intersectUnitSphereSpace(pos, vel, result)) { // no collision
        glm::vec3 dest = pos + vel;
        return dest;
    }

    glm::vec3 intersectPoint = result.hit;
    glm::vec3 originDest = pos + vel;
    glm::vec3 newPos = pos + result.t * vel;

    glm::vec3 slidePlaneNormal = glm::normalize(newPos - intersectPoint);
    newPos += 0.01f * slidePlaneNormal; // adjustment

    Plane slidePlane = Plane(intersectPoint, slidePlaneNormal);
    float signedDistanceToSlidePlane = slidePlane.signedDistanceTo(originDest);
    glm::vec3 newDest = originDest - signedDistanceToSlidePlane * slidePlaneNormal;
    glm::vec3 newVel = newDest - intersectPoint;

    // increment recursion depth
    return collideUnitSphereSpace(newPos, newVel, ++collisionRecursionDepth);
}

bool EllipsoidTriangleCollision::sphereTriangle(const glm::vec3 &pos, const glm::vec3 &vel, const std::shared_ptr<Triangle> &triangle, HitTest &result) const
{
    if (!triangle->isFrontFacingTo(glm::normalize(vel))) {
        // velocity vector is impossible to intersect with triangle
        return false;
    }
    bool intersect = false;
    HitTest temp_result;
    result.t = INFINITY;
    if (sphereInterior(pos, vel, triangle, temp_result) && temp_result.t < result.t) {
        result = temp_result;
        intersect = true;
        //std::cout << "sphere interior collision, t=" << result.t << std::endl;
        return true; // always happen before edge & vertices collision
    }
    // If intersection is outside triangle, continue test on edge and vertices.
    if (sphereEdge(pos, vel, triangle, temp_result) && temp_result.t < result.t) {
        result = temp_result;
        intersect = true;
        //std::cout << "sphere edge collision, hit=" << glm::to_string(result.hit) << "; pos=" << glm::to_string(pos) << ", " << glm::length2(result.hit - pos) << std::endl;
    }
    if (sphereVertex(pos, vel, triangle, temp_result) && temp_result.t < result.t) {
        result = temp_result;
        intersect = true;
        //std::cout << "sphere vertex collision, t=" << result.t << std::endl;
    }
    return intersect;
}

bool EllipsoidTriangleCollision::sphereInterior(const glm::vec3 &pos,
                                                const glm::vec3 &vel,
                                                const std::shared_ptr<Triangle> &triangle,
                                                HitTest &result) const
{
    glm::vec3 closestPoint = pos-triangle->normal;
    if (triangle->intersect(closestPoint, vel, result)) {
        return true;
    }
    return false;
}

bool EllipsoidTriangleCollision::sphereEdge(const glm::vec3 &pos,
                                            const glm::vec3 &vel,
                                            const std::shared_ptr<Triangle> &triangle,
                                            HitTest &result) const
{
    bool intersect = false;
    HitTest temp_result;
    result.t = INFINITY;
    LineSegment lineSegments[3] = {LineSegment(triangle->vertices[0], triangle->vertices[1], 1),
                                   LineSegment(triangle->vertices[1], triangle->vertices[2], 1),
                                   LineSegment(triangle->vertices[2], triangle->vertices[0], 1)};
    for (const LineSegment &lineSegment : lineSegments) {
        if (lineSegment.intersect(pos, vel, temp_result) && temp_result.t < result.t) {
            result = temp_result;
            intersect = true;
        }
    }
    return intersect;
}

bool EllipsoidTriangleCollision::sphereVertex(const glm::vec3 &pos,
                                              const glm::vec3 &vel,
                                              const std::shared_ptr<Triangle> &triangle,
                                              HitTest &result) const
{
    bool intersect = false;
    HitTest temp_result;
    result.t = INFINITY;
    Sphere unitSphere = Sphere(pos, 1);
    for (const glm::vec3 &vertex : triangle->vertices) {
        if (unitSphere.intersect(vertex, -vel, temp_result) && temp_result.t < result.t) {
            result = temp_result;
            result.hit = vertex;
            intersect = true;
        }
    }
    return intersect;
}







