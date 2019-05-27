#include "bulletcollisionresponsecomponent.h"

#include "engine/basics/gameworld.h"
#include "engine/basics/gameobject.h"

BulletCollisionResponseComponent::BulletCollisionResponseComponent(std::shared_ptr<GameWorld> gameWorld, float damage)
    : CollisionResponseComponent("bullet"),
      m_gameWorld(gameWorld),
      m_damage(damage)
{
}


void BulletCollisionResponseComponent::objectCollisionResponse(std::shared_ptr<CollisionResponseComponent> &other){

    m_gameWorld->removeObject(m_gameObject);
}

void BulletCollisionResponseComponent::continuousCollisionResponse() const{

}

float BulletCollisionResponseComponent::getDamage(){
    return m_damage;
}

void BulletCollisionResponseComponent::setDamage(float newDamage){
    m_damage = newDamage;
}
