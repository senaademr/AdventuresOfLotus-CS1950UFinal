#include "cubecollisioncomponent.h"
#include "engine/collisionutils/collisionshape.h"
CubeCollisionComponent::CubeCollisionComponent() :
    CollisionComponent()
{

}

CubeCollisionComponent::~CubeCollisionComponent()
{

}

CollisionShape CubeCollisionComponent::collisionShape() const
{
    return CollisionShape::BOX;
}

bool CubeCollisionComponent::movable() const
{
    return true;
}
