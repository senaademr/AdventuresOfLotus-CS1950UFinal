#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "engine/components/component.h"
#include "engine/util/transform.h"
enum class CollisionShape;
class TransformComponent : public Component
{
public:
    TransformComponent();

    TransformComponent(glm::vec3 position);
    TransformComponent(glm::vec3 position, glm::vec3 size);
    TransformComponent(glm::vec3 position, glm::vec3 size, float angle, glm::vec3 rotation);


    void setPosition(glm::vec3 new_position);

    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);

    void translate(glm::vec3 translation);
    void setSize(float size);
    void setSize(glm::vec3 size);

    void setRotation(float angle, glm::vec3 axis);
    void setAngle(float angle);
    void setRotationAxis(glm::vec3 axis);

    Transform getTransform();
    glm::vec3 getSize();
    glm::vec3 getPosition();

    std::pair<float, glm::vec3> getRotation();

    glm::vec3 getBottom(const CollisionShape &shapeType) const;
    void setBottom(glm::vec3 bottom, const CollisionShape &shapeType);
    glm::vec3 getCenter(const CollisionShape &shapeType) const;
    void setCenter(glm::vec3 center, const CollisionShape &shapeType);
    float getRadius() const;
    glm::vec3 getEllipsoidRadius() const;
    float getHeight() const;

private:
    Transform m_transform;
};

#endif // TRANSFORMCOMPONENT_H
