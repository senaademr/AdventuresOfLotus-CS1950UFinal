#ifndef CONTINUOUSCOLLISIONCOMPONENT_H
#define CONTINUOUSCOLLISIONCOMPONENT_H
#include "component.h"

class TransformComponent;
class EllipsoidTriangleCollision;
class ContinuousCollisionComponent : public Component
{
public:
    ContinuousCollisionComponent(std::shared_ptr<TransformComponent> transformComponent);
    ~ContinuousCollisionComponent() override {}
    std::shared_ptr<EllipsoidTriangleCollision> getEllipsoidTriangleCollision() const;

private:
    std::shared_ptr<EllipsoidTriangleCollision> m_ellipsoidTriangleCollision;
};

#endif // CONTINUOUSCOLLISIONCOMPONENT_H
