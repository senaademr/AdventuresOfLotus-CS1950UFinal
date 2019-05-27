#include "enemycollisionresponsecomponent.h"

#include "engine/components/transformcomponent.h"
#include "engine/components/collisioncomponent.h"
#include "engine/components/timeremovecomponent.h"
//#include "engine/components/animationcomponent.h"
//#include "engine/components/physicscomponent.h"
#include "engine/basics/gameobject.h"
#include "final/final_components/collision_components/bulletcollisionresponsecomponent.h"
#include "final/final_components/enemy_components/enemyabilitycomponent.h"

EnemyCollisionResponseComponent::EnemyCollisionResponseComponent() :
    CollisionResponseComponent("enemy")
{
//    if(!enemyType.compare("spider")){
//        m_dieIndex = 1;
//    }
//    else if(!enemyType.compare("magma")){
//        m_dieIndex = 3;
//    }
//    else if(!enemyType.compare("space")){
//        m_dieIndex = 5;
//    }
//    m_dieIndex = 0;
}

EnemyCollisionResponseComponent::~EnemyCollisionResponseComponent()
{

}
//bool EnemyCollisionResponseComponent::isDead(){
//    return m_isDead;
//}

void EnemyCollisionResponseComponent::objectCollisionResponse(std::shared_ptr<CollisionResponseComponent> &other){

    //if(enemyAbility->isDead()) {
    //    die();
    //    return;
    //}

    if (other->collisionResponseName().compare("bullet") == 0) {
        std::shared_ptr<BulletCollisionResponseComponent> bulletResponse
                = std::dynamic_pointer_cast<BulletCollisionResponseComponent>(other);
        if(!bulletResponse){
            std::cout << "enemy colliding with an object that says its a bullet but isnt a bulletcollisionresponsecomponent" << std::endl;
            return;
        }
        float damage = bulletResponse->getDamage();
        std::shared_ptr<EnemyAbilityComponent> enemyAbility = m_gameObject->getComponent<EnemyAbilityComponent>();
        enemyAbility->dealDamage(damage);
        //if(enemyAbility->isDead()){
        //    die();
        //}
    }
}

//void EnemyCollisionResponseComponent::die() {
//    std::cout << "die animation" << std::endl;
//    m_gameObject->getComponent<AnimationComponent>()->changeAnimation(m_dieIndex);
//    std::shared_ptr<PhysicsComponent> physics = m_gameObject->getComponent<PhysicsComponent>();
//    physics->setXVelocity(0);
//    physics->setZVelocity(0);
//}
