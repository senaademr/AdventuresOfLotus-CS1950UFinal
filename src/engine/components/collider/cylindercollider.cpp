#include "cylindercollider.h"
#include "engine/util/CommonIncludes.h"

#include "collidermath.h"
#include "raycastmath.h"


CylinderCollider::CylinderCollider(std::shared_ptr<TransformComponent> transformComponent)
    : Collider(transformComponent)
{

}

CollisionResponse CylinderCollider::collide(std::shared_ptr<Collider> other){
    return other->collideCylinder(this);
}

CollisionResponse CylinderCollider::collideCylinder(CylinderCollider *other){
    return ColliderMath::collideCylinderCylinder(other, this);
}


CollisionResponse CylinderCollider::collideBox(BoxCollider *other){
    //return ColliderMath::collideCylinderBox(this, other);
    return ColliderMath::collideBoxCylinder(other, this);
}


CollisionResponse CylinderCollider::collideSphere(SphereCollider *other){
    //return ColliderMath::collideCylinderSphere(this, other);
    return ColliderMath::collideSphereCylinder(other, this);
}


RaycastResult CylinderCollider::rayCast(Ray &ray){
    return RaycastMath::castRayCylinder(ray, this);
}
