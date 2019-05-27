#ifndef IMPACTBULLETCOLLISIONRESPONSECOMPONENT_H
#define IMPACTBULLETCOLLISIONRESPONSECOMPONENT_H

#include "bulletcollisionresponsecomponent.h"

class ImpactBulletCollisionResponseComponent : public BulletCollisionResponseComponent
{
public:
    ImpactBulletCollisionResponseComponent(std::shared_ptr<GameWorld> gameWorld, float damage, float impactPower);

    // CollisionResponseComponent interface
public:
    void objectCollisionResponse(std::shared_ptr<CollisionResponseComponent> &other);

private:
    float m_impactPower;
};

#endif // IMPACTBULLETCOLLISIONRESPONSECOMPONENT_H
