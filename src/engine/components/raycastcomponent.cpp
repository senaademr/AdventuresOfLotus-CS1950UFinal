#include "raycastcomponent.h"

#include "engine/systems/collisionsystem.h"

RaycastComponent::RaycastComponent(std::shared_ptr<GameObject> gameObject, std::shared_ptr<CollisionSystem> collisionSystem)
    : Component(gameObject),
      m_collisionSystem(collisionSystem)
{
}


std::shared_ptr<CollisionComponent> RaycastComponent::rayCast(Ray &ray){
    return m_collisionSystem->rayCast(ray);
}
