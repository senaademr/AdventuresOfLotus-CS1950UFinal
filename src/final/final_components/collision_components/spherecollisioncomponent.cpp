#include "spherecollisioncomponent.h"
#include "engine/collisionutils/collisionshape.h"
SphereCollisionComponent::SphereCollisionComponent() :
    CollisionComponent()
{

}

SphereCollisionComponent::~SphereCollisionComponent()
{

}

CollisionShape SphereCollisionComponent::collisionShape() const
{
    return CollisionShape::SPHERE;
}

bool SphereCollisionComponent::movable() const
{
    return true;
}
