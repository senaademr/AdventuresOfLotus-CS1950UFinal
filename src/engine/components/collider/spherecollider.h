#ifndef SPHERECOLLIDER_H
#define SPHERECOLLIDER_H

#include "collider.h"
#include "raycastresult.h"


class SphereCollider : public Collider
{
public:
    SphereCollider(std::shared_ptr<TransformComponent> transformComponent);

    // Collider interface
public:
    CollisionResponse collide(std::shared_ptr<Collider> other) override;
    CollisionResponse collideCylinder(CylinderCollider *other) override;
    CollisionResponse collideBox(BoxCollider *other) override;
    CollisionResponse collideSphere(SphereCollider *other) override;

    RaycastResult rayCast(Ray &ray);
};

#endif // SPHERECOLLIDER_H
