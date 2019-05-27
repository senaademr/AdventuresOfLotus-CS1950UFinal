#ifndef ENEMYCOLLISIONRESPONSECOMPONENT_H
#define ENEMYCOLLISIONRESPONSECOMPONENT_H
#include "engine/components/collisionresponsecomponent.h"
#include "final/abilities/abilityconstants.h"

class  EnemyCollisionResponseComponent : public CollisionResponseComponent
{
public:
    EnemyCollisionResponseComponent();
    ~EnemyCollisionResponseComponent() override;
    void objectCollisionResponse(std::shared_ptr<CollisionResponseComponent> &other) override;

//    bool isDead();

//private:
//    void die();
//    float m_health = AbilityConstants::MAX_HEALTH;
//    bool m_isDead = false;
//    float m_dieIndex;
};
#endif // ENEMYCOLLISIONRESPONSECOMPONENT_H
