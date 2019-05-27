#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include "engine/util/CommonIncludes.h"

class Transform
{
public:
    Transform();
    Transform(glm::vec3 position);
    Transform(glm::vec3 position, glm::vec3 size);
    Transform(glm::vec3 position, glm::vec3 size, float angle, glm::vec3 rotation);
//    Transform(const Transform &other);

    //Needs fix
    Transform combineTransform(Transform &parent);

    Transform translatePosition(glm::vec3 translation) const;
    Transform setPosition(glm::vec3 new_position) const;

    Transform setX(float newX) const;
    Transform setY(float newY) const;
    Transform setZ(float newZ) const;

    Transform setSize(float size) const;
    Transform setSize(glm::vec3 size) const;

    Transform setAngle(float angle) const;
    Transform setRotationAxis(glm::vec3 rotationaxis) const;
    Transform setRotation(float angle, glm::vec3 axis) const;

    glm::vec3 getPosition() const;
    glm::vec3 getSize() const;
    std::pair<float, glm::vec3> getRotation() const;
    glm::vec3 getRotationAxis() const;
    float getAngle() const;

    std::string toString();

private:
    glm::vec3 m_position;
    glm::vec3 m_size;
    float m_angle;
    glm::vec3 m_rotation;
};

#endif // TRANSFORM_H
