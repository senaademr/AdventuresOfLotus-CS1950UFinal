#ifndef PLAYERCOLLISIONRESPONSECOMPONENT_H
#define PLAYERCOLLISIONRESPONSECOMPONENT_H
#include "engine/components/collisionresponsecomponent.h"

class  PlayerCollisionResponseComponent : public CollisionResponseComponent
{
public:
    PlayerCollisionResponseComponent();
    ~PlayerCollisionResponseComponent() override;
    void objectCollisionResponse(std::shared_ptr<CollisionResponseComponent> &other) override;
    void continuousCollisionResponse() const override;

    // CollisionResponseComponent interface
public:

private:
    void sendFlying(std::shared_ptr<CollisionResponseComponent> &other);
};

#endif // PLAYERCOLLISIONRESPONSECOMPONENT_H
