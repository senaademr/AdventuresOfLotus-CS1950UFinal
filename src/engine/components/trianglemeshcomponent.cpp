#include "trianglemeshcomponent.h"

TriangleMeshComponent::TriangleMeshComponent(QList<std::shared_ptr<Triangle>> &collisionTriangles)
    : Component(),
      m_collisionTriangles(collisionTriangles)
{

}

QList<std::shared_ptr<Triangle> >& TriangleMeshComponent::getCollisionTriangles() {
    return m_collisionTriangles;
}
