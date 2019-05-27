#include "cylindercollisioncomponent.h"
#include "engine/collisionutils/collisionshape.h"
CylinderCollisionComponent::CylinderCollisionComponent() :
    CollisionComponent()
{

}

CylinderCollisionComponent::~CylinderCollisionComponent()
{

}

CollisionShape CylinderCollisionComponent::collisionShape() const
{
    return CollisionShape::CYLINDER;
}

bool CylinderCollisionComponent::movable() const
{
    return true;
}

