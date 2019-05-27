#ifndef SPHERECOLLISIONCOMPONENT_H
#define SPHERECOLLISIONCOMPONENT_H
#include "engine/components/collisioncomponent.h"

class SphereCollisionComponent : public CollisionComponent
{
public:
    SphereCollisionComponent();
    ~SphereCollisionComponent() override;
    CollisionShape collisionShape() const override;
    bool movable() const override;
};

#endif // SPHERECOLLISIONCOMPONENT_H
