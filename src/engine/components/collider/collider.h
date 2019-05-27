#ifndef COLLIDER_H
#define COLLIDER_H

#include "engine/util/CommonIncludes.h"
#include "engine/components/collider/collisionresponse.h"
#include "raycastresult.h"

class CylinderCollider;
class BoxCollider;
class SphereCollider;
class CollisionComponent;
class CompoundCollider;
class GameObject;
class TransformComponent;
class Transform;
class Ray;


class Collider
{
public:
    Collider(std::shared_ptr<TransformComponent> transformComponent);
    virtual ~Collider();

    virtual CollisionResponse collide(std::shared_ptr<Collider> other) = 0;
    virtual CollisionResponse collideCylinder(CylinderCollider* other) = 0;
    virtual CollisionResponse collideBox(BoxCollider* other) = 0;
    virtual CollisionResponse collideSphere(SphereCollider *other) = 0;

    virtual RaycastResult rayCast(Ray &ray) = 0;

    //std::shared_ptr<GameObject> getGameObject();
    std::shared_ptr<TransformComponent> getTransformComponent();
    Transform getTransform();


    void setParentTransform(std::shared_ptr<TransformComponent> parent);

private:
    std::shared_ptr<TransformComponent> m_transformComponent;
    std::shared_ptr<TransformComponent> m_parentTransformComponent;
};

#endif // COLLIDER_H
