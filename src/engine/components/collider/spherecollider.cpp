#include "spherecollider.h"

#include "collidermath.h"
#include "raycastmath.h"

SphereCollider::SphereCollider(std::shared_ptr<TransformComponent> transformComponent) :
    Collider(transformComponent)
{

}

CollisionResponse SphereCollider::collide(std::shared_ptr<Collider> other) {
    return other->collideSphere(this);

}
CollisionResponse SphereCollider::collideCylinder(CylinderCollider *other) {
    return ColliderMath::collideCylinderSphere(other, this);
}
CollisionResponse SphereCollider::collideBox(BoxCollider *other){
    return ColliderMath::collideBoxSphere(other, this);
}
CollisionResponse SphereCollider::collideSphere(SphereCollider *other){
    return ColliderMath::collideSphereSphere(other, this);
}

RaycastResult SphereCollider::rayCast(Ray &ray){
    return RaycastMath::castRaySphere(ray, this);
}
