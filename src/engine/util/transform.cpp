#include "transform.h"

#include <string>
#include <iostream>

Transform::Transform():
    m_position(glm::vec3(0)),
    m_size(1.f)
{
}

Transform::Transform(glm::vec3 position) :
    m_position(position)
{

}

Transform::Transform(glm::vec3 position, glm::vec3 size) :
    m_position(position),
    m_size(size)
{

}

Transform::Transform(glm::vec3 position, glm::vec3 size, float angle, glm::vec3 rotation) :
    m_position(position),
    m_size(size),
    m_angle(angle),
    m_rotation(rotation)
{

}
/**
 * @brief Transform::combineTransform
 *
 * @param other
 * @return
 */
Transform Transform::combineTransform(Transform &parent){
    if(parent.getSize().x == 1 && parent.getSize().y == 1 && parent.getSize().z == 1
            && parent.getPosition().x == 0 && parent.getPosition().y == 0 && parent.getPosition().z == 0){
        return *this;
    }
    glm::vec3 otherSize = parent.getSize();
    glm::vec3 size = glm::vec3(m_size.x *otherSize.x,
                               m_size.y *otherSize.y,
                               m_size.z *otherSize.z);
    glm::vec3 position = this->getPosition();
    position = glm::vec3(position.x * otherSize.x,
                         position.y * otherSize.y,
                         position.z * otherSize.z);
    position += parent.getPosition();
    Transform t = Transform(position, size);
    return t;

}

Transform Transform::setPosition(glm::vec3 new_position) const{
    Transform t = Transform(new_position, this->getSize(), this->getAngle(), this->getRotationAxis());
    return t;
}
Transform Transform::translatePosition(glm::vec3 translation) const{
    Transform t = Transform(this->getPosition() + translation, this->getSize(), this->getAngle(), this->getRotationAxis());
    return t;
}

Transform Transform::setX(float newX) const{
    glm::vec3 position = glm::vec3(newX, m_position.y, m_position.z);
    Transform t = Transform(position, this->getSize(), this->getAngle(), this->getRotationAxis());
    return t;
    //m_position = glm::vec3(newX, m_position.y, m_position.z);
}
Transform Transform::setY(float newY) const{
    glm::vec3 position = glm::vec3(m_position.x, newY, m_position.z);
    Transform t = Transform(position, this->getSize(), this->getAngle(), this->getRotationAxis());
    return t;
    //m_position = glm::vec3(m_position.x, newY, m_position.z);
}
Transform Transform::setZ(float newZ) const{
    glm::vec3 position = glm::vec3(m_position.x, m_position.y, newZ);
    Transform t = Transform(position, this->getSize(), this->getAngle(), this->getRotationAxis());
    return t;
    //m_position = glm::vec3(m_position.x, m_position.y, newZ);
}

Transform Transform::setSize(float size) const{
    glm::vec3 newSize = glm::vec3(size, size, size);
    Transform t = Transform(this->getPosition(), newSize, this->getAngle(), this->getRotationAxis());
    return t;
}


Transform Transform::setSize(glm::vec3 size) const{
    Transform t = Transform(this->getPosition(), size, this->getAngle(), this->getRotationAxis());
    return t;
}

Transform Transform::setAngle(float angle) const{
    Transform t = Transform(this->getPosition(), this->getSize(), angle, this->getRotationAxis());
    return t;
}
Transform Transform::setRotationAxis(glm::vec3 rotationaxis) const{
    Transform t = Transform(this->getPosition(), this->getSize(), this->getAngle(), rotationaxis);
    return t;
}

Transform Transform::setRotation(float angle, glm::vec3 axis) const{
    Transform t = Transform(this->getPosition(), this->getSize(), angle, axis);
    return t;
}

glm::vec3 Transform::getPosition() const{
    return m_position;
}

glm::vec3 Transform::getSize() const{
    return m_size;
}

std::pair<float, glm::vec3> Transform::getRotation() const{
    return std::pair<float, glm::vec3>(m_angle, m_rotation);
}

glm::vec3 Transform::getRotationAxis() const{
    return m_rotation;
}

float Transform::getAngle() const{
    return m_angle;
}

std::string Transform::toString(){
    return "Transform. Pos: " + glm::to_string(this->getPosition()) + "    Size: " + glm::to_string(this->getSize());
}

