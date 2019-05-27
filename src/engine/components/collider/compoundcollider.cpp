#include "compoundcollider.h"

#include "collidermath.h"
#include "collider.h"
#include "raycastmath.h"

CompoundCollider::CompoundCollider(std::shared_ptr<TransformComponent> transformComponent)
    : Collider(transformComponent),
      m_boundingCollider(nullptr)
{
}




void CompoundCollider::addCollider(std::shared_ptr<Collider> collider){
    collider->setParentTransform(this->getTransformComponent());
    this->m_colliders.append(collider);

}

void CompoundCollider::addColliderList(QList<std::shared_ptr<Collider>> colliders){
    for(std::shared_ptr<Collider> collider : colliders){
        addCollider(collider);
    }
}

QList<std::shared_ptr<Collider> > CompoundCollider::getColliders(){
    return m_colliders;
}


void CompoundCollider::setBoundingCollider(std::shared_ptr<Collider> boundingCollider){
    m_boundingCollider = boundingCollider;
}


std::shared_ptr<Collider> CompoundCollider::getBoundingCollider(){
    return m_boundingCollider;
}

bool CompoundCollider::hasBoundingCollider(){
    return m_boundingCollider != nullptr;
}

CollisionResponse CompoundCollider::collide(std::shared_ptr<Collider> other){
    throw "cannot collide directly with compound";

    //return other->collideCompound(this);
}

CollisionResponse CompoundCollider::collideCylinder(CylinderCollider *other){
    throw "cannot collide directly with compound";

    //return ColliderMath::collideCylinderCompound(other, this);
}

CollisionResponse CompoundCollider::collideBox(BoxCollider *other){
    throw "cannot collide directly with compound";
    //return ColliderMath::collideBoxCompound(other, this);

}

CollisionResponse CompoundCollider::collideSphere(SphereCollider *other){
    throw "cannot collide directly with compound";
    //return ColliderMath::collideSphereCompound(other, this);

}



RaycastResult CompoundCollider::rayCast(Ray &ray){
    return RaycastMath::castRayCompound(ray, this);
}
