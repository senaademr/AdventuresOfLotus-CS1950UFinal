#include "transformcomponent.h"
#include "collisioncomponent.h"
#include "engine/collisionutils/collisionshape.h"
#include <string>

TransformComponent::TransformComponent()
    : Component() ,
    m_transform(Transform())
{

}

TransformComponent::TransformComponent(glm::vec3 position) :
    Component(),
    m_transform(position)
{

}

TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 size)
    : Component(),
    m_transform(position, size)
{

}

TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 size, float angle, glm::vec3 rotation)
    : Component() ,
    m_transform(position, size, angle, rotation)
{

}

glm::vec3 TransformComponent::getPosition(){
    return m_transform.getPosition();
}

std::pair<float, glm::vec3> TransformComponent::getRotation(){
    return m_transform.getRotation();
}
void TransformComponent::setPosition(glm::vec3 new_position){
    m_transform = m_transform.setPosition(new_position);
}
void TransformComponent::translate(glm::vec3 translation){
    m_transform = m_transform.translatePosition(translation);
}

void TransformComponent::setX(float newX){
    m_transform = m_transform.setX(newX);
}
void TransformComponent::setY(float newY){
    m_transform = m_transform.setY(newY);
}
void TransformComponent::setZ(float newZ){
    m_transform = m_transform.setZ(newZ);

}

void TransformComponent::setSize(float size){
    m_transform = m_transform.setSize(size);
}


void TransformComponent::setSize(glm::vec3 size){
    m_transform = m_transform.setSize(size);
}


Transform TransformComponent::getTransform(){
    return m_transform;
}

glm::vec3 TransformComponent::getSize(){

    return m_transform.getSize();
}

void TransformComponent::setAngle(float angle){
    m_transform = m_transform.setAngle(angle);
}

void TransformComponent::setRotationAxis(glm::vec3 axis){
    m_transform = m_transform.setRotationAxis(axis);
}

void TransformComponent::setRotation(float angle, glm::vec3 axis){
    m_transform = m_transform.setRotation(angle, axis);
}
glm::vec3 TransformComponent::getBottom(const CollisionShape &shapeType) const {
    switch(shapeType) {
    case(CollisionShape::BOX):
    case(CollisionShape::SPHERE):
        return m_transform.getPosition() - (m_transform.getSize() * glm::vec3(0, .5f, 0));
    }
    return m_transform.getPosition();
}

void TransformComponent::setBottom(glm::vec3 bottom, const CollisionShape &shapeType)
{
    glm::vec3 newPosition;
    switch(shapeType) {
    case(CollisionShape::BOX):
    case(CollisionShape::SPHERE):
        newPosition = bottom + (m_transform.getSize() * glm::vec3(0, .5f, 0));
        break;
    default:
        newPosition = bottom;
    }
    setPosition(newPosition);
}

glm::vec3 TransformComponent::getCenter(const CollisionShape &shapeType) const {
    switch(shapeType) {
    case(CollisionShape::BOX):
    case(CollisionShape::SPHERE):
        return m_transform.getPosition();
    }
    return m_transform.getPosition() + (m_transform.getSize() * glm::vec3(0, .5f, 0));
}
void TransformComponent::setCenter(glm::vec3 center, const CollisionShape &shapeType){
    glm::vec3 newPosition;
    switch(shapeType) {
    case(CollisionShape::BOX):
    case(CollisionShape::SPHERE):
        newPosition = center;
        break;
    default:
        newPosition = center - (m_transform.getSize() * glm::vec3(0, .5f, 0));
    }    
    setPosition(newPosition);
}
float TransformComponent::getRadius() const {
    assert(m_transform.getSize().x == m_transform.getSize().z);
    return m_transform.getSize().x * 0.5f;
}
glm::vec3 TransformComponent::getEllipsoidRadius() const {
    return m_transform.getSize() * 0.5f;
}
float TransformComponent::getHeight() const {
    return m_transform.getSize().y;
}
