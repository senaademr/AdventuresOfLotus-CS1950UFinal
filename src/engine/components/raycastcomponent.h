#ifndef RAYCASTCOMPONENT_H
#define RAYCASTCOMPONENT_H

#include "component.h"
class Ray;
class CollisionSystem;
class CollisionComponent;

class RaycastComponent : public Component
{
public:
    RaycastComponent(std::shared_ptr<GameObject> gameObject, std::shared_ptr<CollisionSystem> collisionSystem);

    std::shared_ptr<CollisionComponent> rayCast(Ray &ray);

private:
    std::shared_ptr<CollisionSystem> m_collisionSystem;

};

#endif // RAYCASTCOMPONENT_H
