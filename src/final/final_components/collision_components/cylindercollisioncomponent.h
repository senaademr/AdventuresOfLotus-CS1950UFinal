#ifndef CYLINDERCOLLISIONCOMPONENT_H
#define CYLINDERCOLLISIONCOMPONENT_H
#include "engine/components/collisioncomponent.h"

class CylinderCollisionComponent : public CollisionComponent
{
public:
    CylinderCollisionComponent();
    ~CylinderCollisionComponent() override;
    CollisionShape collisionShape() const override;
    bool movable() const override;
};

#endif // CYLINDERCOLLISIONCOMPONENT_H
