#ifndef COMPOUNDCOLLIDER_H
#define COMPOUNDCOLLIDER_H

#include <QList>
#include <memory>

#include "collider.h"
#include "raycastresult.h"


class CompoundCollider : public Collider
{
public:
    CompoundCollider(std::shared_ptr<TransformComponent> transformComponent);

    void addCollider(std::shared_ptr<Collider> collider);
    void addColliderList(QList<std::shared_ptr<Collider>> colliders);
    QList<std::shared_ptr<Collider>> getColliders();
    void setBoundingCollider(std::shared_ptr<Collider> boundingCollider);
    std::shared_ptr<Collider> getBoundingCollider();
    bool hasBoundingCollider();

    // Collider interface
public:
    //Dont actually call these
    CollisionResponse collide(std::shared_ptr<Collider> other) override;
    CollisionResponse collideCylinder(CylinderCollider *other) override;
    CollisionResponse collideBox(BoxCollider *other) override;
    CollisionResponse collideSphere(SphereCollider *other) override;

    //safe to call but will always return false
    RaycastResult rayCast(Ray &ray);



private:
    QList<std::shared_ptr<Collider>> m_colliders;
    std::shared_ptr<Collider> m_boundingCollider;
};

#endif // COMPOUNDCOLLIDER_H
