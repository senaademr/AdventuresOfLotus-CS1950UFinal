#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "collider.h"
#include "raycastresult.h"



class BoxCollider : public Collider
{
public:
    BoxCollider(std::shared_ptr<TransformComponent> transformComponent);
    // Collider interface
public:
    CollisionResponse collide(std::shared_ptr<Collider> other) override;
    CollisionResponse collideCylinder(CylinderCollider *other) override;
    CollisionResponse collideBox(BoxCollider *other) override;
    CollisionResponse collideSphere(SphereCollider *other) override;

    RaycastResult rayCast(Ray &ray);
};

#endif // BOXCOLLIDER_H
