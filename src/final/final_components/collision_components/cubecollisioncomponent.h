#ifndef CUBECOLLISIONCOMPONENT_H
#define CUBECOLLISIONCOMPONENT_H
#include "engine/components/collisioncomponent.h"

class CubeCollisionComponent : public CollisionComponent
{
public:
    CubeCollisionComponent();
    ~CubeCollisionComponent() override;
    CollisionShape collisionShape() const override;
    bool movable() const override;
};

#endif // CUBECOLLISIONCOMPONENT_H
