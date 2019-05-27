#include "collider.h"
#include "engine/components/collisioncomponent.h"
#include "engine/components/transformcomponent.h"
#include "engine/basics/gameobject.h"
#include "engine/components/physicscomponent.h"

/*
Collider::Collider(CollisionComponent* collisionComponent) :
    m_collisionComponent(collisionComponent)
{

}*/
Collider::Collider(std::shared_ptr<TransformComponent> transformComponent) :
    m_transformComponent(transformComponent),
    m_parentTransformComponent(std::make_shared<TransformComponent>(transformComponent->getGameObject()))
{

}

Collider::~Collider(){}

void Collider::setParentTransform(std::shared_ptr<TransformComponent> parent){
    m_parentTransformComponent = parent;
}

std::shared_ptr<TransformComponent> Collider::getTransformComponent(){
    return m_transformComponent;
}

Transform Collider::getTransform(){
    Transform parentTransform = m_parentTransformComponent->getTransform();
    Transform thisTransform = m_transformComponent->getTransform();
    return thisTransform.combineTransform(parentTransform);
}
