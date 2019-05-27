#include "boxcollider.h"

#include "collidermath.h"
#include "raycastmath.h"

BoxCollider::BoxCollider(std::shared_ptr<TransformComponent> transformComponent)
    : Collider(transformComponent)
{

}

CollisionResponse BoxCollider::collide(std::shared_ptr<Collider> other) {
    return other->collideBox(this);
}

CollisionResponse BoxCollider::collideCylinder(CylinderCollider *other) {
    //std::cout << "this one" << std::endl;
    return ColliderMath::collideCylinderBox(other, this);

}
CollisionResponse BoxCollider::collideBox(BoxCollider *other) {
    return ColliderMath::collideBoxBox(other, this);
}
CollisionResponse BoxCollider::collideSphere(SphereCollider *other){
    //return ColliderMath::collideBoxSphere(this, other);
    return ColliderMath::collideSphereBox(other, this);
}

RaycastResult BoxCollider::rayCast(Ray &ray){
    return RaycastMath::castRayBox(ray, this);
}
