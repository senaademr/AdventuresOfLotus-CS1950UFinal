#include "collisionsystem.h"

#include <math.h>

#include "engine/basics/gameobject.h"
#include "engine/components/collisioncomponent.h"
#include "engine/components/transformcomponent.h"
#include "engine/components/physicscomponent.h"
#include "engine/components/collisionresponsecomponent.h"
#include "engine/components/continuouscollisioncomponent.h"
#include "engine/collisionutils/collisionshape.h"
#include "engine/collisionutils/ray.h"
#include "engine/collisionutils/floor.h"

#include "engine/systems/continuouscollisionsystem.h"
#include "engine/graphics/Camera.h"

CollisionSystem::CollisionSystem(std::shared_ptr<Camera> &camera
                                 , std::shared_ptr<ContinuousCollisionSystem> continuousCollisionSystem)
    : TickSystem(TypeID::value<CollisionComponent>()),
    m_camera(camera),
    m_continuousCollisionSystem(continuousCollisionSystem)
{
}

void CollisionSystem::tick(float seconds){
    // Checks for collisions between objects
    // Notifies objects that they have collided
    auto set_end = m_components.end();
    for (auto ai = m_components.begin(); ai != set_end; ++ai)
    {
        std::shared_ptr<CollisionComponent> a = std::dynamic_pointer_cast<CollisionComponent>(*ai);
        rayCollision(a); // all collidable objs
        for (auto bi = std::next(ai); bi != set_end; ++bi)
        {
            std::shared_ptr<CollisionComponent> b = std::dynamic_pointer_cast<CollisionComponent>(*bi);
            if (!a->movable() && !b->movable())
            {
                continue;
            }
            mutualCollision(a, b); // all pair of collidable objs
        }
    }
}

void CollisionSystem::rayCollision(std::shared_ptr<CollisionComponent> &c)
{
//    Ray ray(m_camera->getEye(), m_camera->getLook());
//    aabBox(ray, c);
}

void CollisionSystem::mutualCollision(std::shared_ptr<CollisionComponent> &a, std::shared_ptr<CollisionComponent> &b)
{
    assert(((a->movable() || b->movable()) && "AT least one is MOVABLE")); // make sure at least one object is movable
    glm::vec3 mtv(0.f);
    // collision detection
    std::shared_ptr<TransformComponent> transformComponentA = a->getGameObject()->getComponent<TransformComponent>();
    std::shared_ptr<TransformComponent> transformComponentB = b->getGameObject()->getComponent<TransformComponent>();

    glm::vec3 positionA = transformComponentA->getBottom(a->collisionShape());
    glm::vec3 dimensionA = transformComponentA->getSize();
    float radiusA = transformComponentA->getRadius();
    float heightA = transformComponentA->getHeight();
    glm::vec3 centerA = transformComponentA->getCenter(a->collisionShape());

    glm::vec3 positionB = transformComponentB->getBottom(b->collisionShape());
    glm::vec3 dimensionB = transformComponentB->getSize();
    float radiusB = transformComponentB->getRadius();
    float heightB = transformComponentB->getHeight();
    glm::vec3 centerB = transformComponentB->getCenter(b->collisionShape());

    // calculate MTV in the direction of B
    if (a->collisionShape() == CollisionShape::CUSTUM)
    {
        // pass to A
        mtv = a->customCollision(b);
        if (a->hasFloor())
        {
            b->addFloor(a->floor());
        }
    }
    else if (b->collisionShape() == CollisionShape::CUSTUM)
    {
        // pass to B
        mtv = -b->customCollision(a);
        if (b->hasFloor())
        {
            a->addFloor(b->floor());
        }
    }
    else if (a->collisionShape() == CollisionShape::BOX && b->collisionShape() == CollisionShape::BOX)
    {
        // in the direction of B
        mtv = CollisionComponent::boxBox(positionA, dimensionA, positionB, dimensionB);
    }
    else if (a->collisionShape() == CollisionShape::SPHERE && b->collisionShape() == CollisionShape::SPHERE)
    {
        // in the direction of B
        mtv = CollisionComponent::sphereSphere(centerA, radiusA, centerB, radiusB);
    }
    else if (a->collisionShape() == CollisionShape::CYLINDER && b->collisionShape() == CollisionShape::CYLINDER)
    {
        // in the direction of B
        mtv = CollisionComponent::cylinderCylinder(positionA, radiusA, heightA, positionB, radiusB, heightB);
    }
    else if (a->collisionShape() == CollisionShape::BOX && b->collisionShape() == CollisionShape::CYLINDER)
    {
        // in the direction of B
        mtv = CollisionComponent::boxCylinder(positionA, dimensionA, positionB, radiusB, heightB);
    }
    else if (a->collisionShape() == CollisionShape::CYLINDER && b->collisionShape() == CollisionShape::BOX)
    {
        // in the direction of A so -
        mtv = -CollisionComponent::boxCylinder(positionB, dimensionB, positionA, radiusA, heightA);
    }
    else if (a->collisionShape() == CollisionShape::BOX && b->collisionShape() == CollisionShape::SPHERE)
    {
        // in the direction of B
        mtv = CollisionComponent::boxSphere(positionA, dimensionA, centerB, radiusB);
    }
    else if (a->collisionShape() == CollisionShape::SPHERE && b->collisionShape() == CollisionShape::BOX)
    {
        // in the direction of A so -
        mtv = -CollisionComponent::boxSphere(positionB, dimensionB, centerA, radiusA);
    }
    else if (a->collisionShape() == CollisionShape::CYLINDER && b->collisionShape() == CollisionShape::SPHERE)
    {
        // in the direction of B
        mtv = CollisionComponent::cylinderSphere(positionA, radiusA, heightA, centerB, radiusB);
    }
    else if (a->collisionShape() == CollisionShape::SPHERE && b->collisionShape() == CollisionShape::CYLINDER)
    {
        // in the direction of A so -
        mtv = -CollisionComponent::cylinderSphere(positionB, radiusB, heightB, centerA, radiusA);
    }

    collisionResponse(a, b, mtv);
    a->collideFloor();
    b->collideFloor();
}

void CollisionSystem::aabBox(const Ray &ray, std::shared_ptr<CollisionComponent> &c)
{
    float t(0.f);
    bool intersect = c->aabBox(ray, t);
    std::shared_ptr<CollisionResponseComponent> responseComponent = c->getGameObject()->getComponent<CollisionResponseComponent>();
    responseComponent->collideRay(ray, t, intersect);
}

void CollisionSystem::collisionResponse(std::shared_ptr<CollisionComponent> &a,
                                        std::shared_ptr<CollisionComponent> &b, const glm::vec3 &mtv)
{
    if (glm::length2(mtv) == 0.f)
    {
        return;
    }

    //std::cout << int(a->collisionShape()) << " collides " << int(b->collisionShape()) << " " << glm::to_string(mtv) << std::endl;
    glm::vec3 aMtv, bMtv;
    if (!a->movable())
    {
        aMtv = glm::vec3(0);
        bMtv = mtv;
    } else if (!b->movable())
    {
        aMtv = -mtv;
        bMtv = glm::vec3(0);
    } else {
        // both a & b are movable
        aMtv = -0.5f * mtv;
        bMtv = 0.5f * mtv;
    }

    std::shared_ptr<GameObject> objectA = a->getGameObject();
    std::shared_ptr<GameObject> objectB = b->getGameObject();

    std::shared_ptr<CollisionResponseComponent> responseComponentA = objectA->getComponent<CollisionResponseComponent>();
    std::shared_ptr<CollisionResponseComponent> responseComponentB = objectB->getComponent<CollisionResponseComponent>();

    glm::vec3 adjustmentToB = responseComponentA->collideObject(aMtv, responseComponentB);
    glm::vec3 adjustmentToA = responseComponentB->collideObject(bMtv, responseComponentA);

    if (glm::length2(adjustmentToA) < glm::length2(adjustmentToB)) { // select a shorter adjustment
        responseComponentA->collideObject(adjustmentToA, responseComponentB);
    } else {
        responseComponentB->collideObject(adjustmentToB, responseComponentA);
    }
}
