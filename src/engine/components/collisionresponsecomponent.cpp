#include "collisionresponsecomponent.h"

#include "engine/collisionutils/ellipsoidtrianglecollision.h"
#include "physicscomponent.h"
#include "transformcomponent.h"
#include "collisioncomponent.h"
#include "continuouscollisioncomponent.h"
#include "objectdrawcomponent.h"
#include "engine/basics/gameobject.h"
CollisionResponseComponent::CollisionResponseComponent(std::string collisionResponseName) :
    Component(),
    m_collisionResponseName(collisionResponseName)
{

}

CollisionResponseComponent::~CollisionResponseComponent()
{

}

// collide with an object and return the adjustment needed to the object it collides with in the case of colliding with terrian
glm::vec3 CollisionResponseComponent::collideObject(const glm::vec3 &mtv, std::shared_ptr<CollisionResponseComponent> &other)
{
    assert(m_gameObject);
    objectCollisionResponse(other); // the other object's response to collision
    if (m_gameObject->hasComponent<ContinuousCollisionComponent>()) {
        return collideContinuous(mtv); // handle continuous collision
    } else {
        std::shared_ptr<TransformComponent> transform = m_gameObject->getComponent<TransformComponent>();
        transform->translate(mtv); // handle object movement
    }
    return glm::vec3(0.f);
}

// collide with a ray
void CollisionResponseComponent::collideRay(const Ray &ray, const float &t, const bool &intersect) const
{
//    std::shared_ptr<ObjectDrawComponent> drawableComponent = m_gameObject->getComponent<ObjectDrawComponent>();
//    if (intersect)
//    {
//        drawableComponent->setMaterial("redColor");
//    } else if (drawableComponent->getMaterial() == "redColor") {
//        drawableComponent->setMaterial("");
//    }
}

// collide with terrian and return the difference of result movement and target movement
glm::vec3 CollisionResponseComponent::collideContinuous(const glm::vec3 &movement) const {
    assert(m_gameObject);
    std::shared_ptr<TransformComponent> transform = m_gameObject->getComponent<TransformComponent>();
    std::shared_ptr<PhysicsComponent> physics = m_gameObject->getComponent<PhysicsComponent>();
    std::shared_ptr<CollisionComponent> collision = m_gameObject->getComponent<CollisionComponent>();
    std::shared_ptr<ContinuousCollisionComponent> continuous = m_gameObject->getComponent<ContinuousCollisionComponent>();
    glm::vec3 startEllipsoidCenter = transform->getCenter(collision->collisionShape()); // center of collision shape
    glm::vec3 endEllipsoidCenter = startEllipsoidCenter + movement;

    bool collided = false;
    std::shared_ptr<EllipsoidTriangleCollision> ellipsoidTriangleCollision = continuous->getEllipsoidTriangleCollision();
    glm::vec3 resultEllipsoidCenter = ellipsoidTriangleCollision->continuousCollisionResponse(startEllipsoidCenter, endEllipsoidCenter, collided);

//    std::cout << "new position: " << resultEllipsoidCenter << std::endl;
    transform->setCenter(resultEllipsoidCenter, collision->collisionShape());

    if (collided) {
        continuousCollisionResponse(); // handle continuous collision response
        physics->setYVelocity(0); // stop Y velocity by default
        return (resultEllipsoidCenter - startEllipsoidCenter) - movement;
    }
    return glm::vec3(0.f);
}

const std::string CollisionResponseComponent::collisionResponseName() const {
    return m_collisionResponseName;
}

void CollisionResponseComponent::objectCollisionResponse(std::shared_ptr<CollisionResponseComponent> &other) {
    // any response for the other object
}

void CollisionResponseComponent::continuousCollisionResponse() const {
    // any response when hit the ground
}








