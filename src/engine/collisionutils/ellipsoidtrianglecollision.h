#ifndef ELLIPSOIDTRIANGLECOLLISION_H
#define ELLIPSOIDTRIANGLECOLLISION_H
#include <QList>
#include "glm/glm.hpp"
#include <memory>
#include "hittest.h"

class Triangle;
class Ellipsoid;
class EllipsoidTriangleCollision
{
public:
    EllipsoidTriangleCollision(glm::vec3 radius);

    ~EllipsoidTriangleCollision() {}

    void updateTriangles(const QList<std::shared_ptr<Triangle>> &triangles);

    bool continuousCollisionTest(const glm::vec3 &start, const glm::vec3 &end, HitTest &result) const;
    bool intersectUnitSphereSpace(const glm::vec3 &pos, const glm::vec3 &vel, HitTest &result) const;
    glm::vec3 continuousCollisionResponse(const glm::vec3 &start, const glm::vec3 &end, bool &collided) const;
    glm::vec3 collideUnitSphereSpace(const glm::vec3 &pos, const glm::vec3 &vel, int &collisionRecursionDepth) const;

    bool sphereTriangle(const glm::vec3 &pos, const glm::vec3 &vel, const std::shared_ptr<Triangle> &triangle, HitTest &result) const;
    bool sphereInterior(const glm::vec3 &pos, const glm::vec3 &vel, const std::shared_ptr<Triangle> &triangle, HitTest &result) const;
    bool sphereEdge(const glm::vec3 &pos, const glm::vec3 &vel, const std::shared_ptr<Triangle> &triangle, HitTest &result) const;
    bool sphereVertex(const glm::vec3 &pos, const glm::vec3 &vel, const std::shared_ptr<Triangle> &triangle, HitTest &result) const;

    const std::shared_ptr<Ellipsoid> ellipsoid;


private:
    QList<std::shared_ptr<Triangle>> m_triangles; // in unit sphere space
};

#endif // ELLIPSOIDTRIANGLECOLLISION_H
