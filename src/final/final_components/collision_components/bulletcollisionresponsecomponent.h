#ifndef BULLETCOLLISIONRESPONSECOMPONENT_H
#define BULLETCOLLISIONRESPONSECOMPONENT_H

#include "engine/components/collisionresponsecomponent.h"
class GameWorld;

class BulletCollisionResponseComponent : public CollisionResponseComponent
{
public:
    BulletCollisionResponseComponent(std::shared_ptr<GameWorld> gameWorld, float damage);

    // CollisionResponseComponent interface
public:
    void objectCollisionResponse(std::shared_ptr<CollisionResponseComponent> &other) override;
    void continuousCollisionResponse() const override;

    float getDamage();
    void setDamage(float newDamage);

private:
    std::shared_ptr<GameWorld> m_gameWorld;
    float m_damage;
};

#endif // BULLETCOLLISIONRESPONSECOMPONENT_H
