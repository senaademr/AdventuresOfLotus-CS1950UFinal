#ifndef COLLISIONRESPONSECOMPONENT_H
#define COLLISIONRESPONSECOMPONENT_H

#include "engine/components/component.h"
#include <QList>

class Triangle;
struct Ray;
class CollisionResponseComponent : public Component
{
public:
    CollisionResponseComponent(std::string collisionResponseName);
    virtual ~CollisionResponseComponent();

    glm::vec3 collideObject(const glm::vec3 &mtv, std::shared_ptr<CollisionResponseComponent> &other);
    glm::vec3 collideContinuous(const glm::vec3 &movement) const;

    virtual const std::string collisionResponseName() const;
    virtual void objectCollisionResponse(std::shared_ptr<CollisionResponseComponent> &other);
    virtual void continuousCollisionResponse() const;
    virtual void collideRay(const Ray &ray, const float &t, const bool &intersect) const;
private:
    const std::string m_collisionResponseName;
};

#endif // COLLISIONRESPONSECOMPONENT_H
