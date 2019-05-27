#include "continuouscollisioncomponent.h"
#include "engine/collisionutils/ellipsoidtrianglecollision.h"
#include "engine/components/transformcomponent.h"
#include "engine/basics/gameobject.h"

ContinuousCollisionComponent::ContinuousCollisionComponent(std::shared_ptr<TransformComponent> transformComponent) :
    Component(),
    m_ellipsoidTriangleCollision(std::make_shared<EllipsoidTriangleCollision>(transformComponent->getEllipsoidRadius()))
{

}
std::shared_ptr<EllipsoidTriangleCollision> ContinuousCollisionComponent::getEllipsoidTriangleCollision() const {
    return m_ellipsoidTriangleCollision;
}
