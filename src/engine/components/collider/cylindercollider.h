#ifndef CYLINDERCOLLIDER_H
#define CYLINDERCOLLIDER_H

#include "collider.h"
#include "raycastresult.h"
#include "engine/util/CommonIncludes.h"

class TransformComponent;

class CylinderCollider : public Collider
{
public:
    CylinderCollider(std::shared_ptr<TransformComponent> transformComponent);

    // Collider interface
public:
    CollisionResponse collide(std::shared_ptr<Collider> other) override;
    CollisionResponse collideCylinder(CylinderCollider *other) override;
    CollisionResponse collideBox(BoxCollider *other) override;
    CollisionResponse collideSphere(SphereCollider *other) override;

    RaycastResult rayCast(Ray &ray);

private:

};

#endif // CYLINDERCOLLIDER_H
