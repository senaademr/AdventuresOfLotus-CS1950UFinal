#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "ticksystem.h"

//#include "engine/components/collider/collisionresponse.h"

class CollisionComponent;
class Ray;
class Camera;
class ContinuousCollisionSystem;

class CollisionSystem : public TickSystem
{
public:
    CollisionSystem(std::shared_ptr<Camera> &camera, std::shared_ptr<ContinuousCollisionSystem> continuousCollisionSystem);

    std::shared_ptr<CollisionComponent> rayCast(Ray &ray);

    // TickSystem interface
public:
    void tick(float seconds);

    void rayCollision(std::shared_ptr<CollisionComponent> &c);
    void mutualCollision(std::shared_ptr<CollisionComponent> &a, std::shared_ptr<CollisionComponent> &b);

//private:

//    bool isInvalidMtv( glm::vec3 mtv);
//    void resolveMtv(std::shared_ptr<CollisionComponent> collisionComponent1,
//                                  std::shared_ptr<CollisionComponent> collisionComponent2, glm::vec3 mtv);

//    void fixVelocity(std::shared_ptr<GameObject> object, glm::vec3 mtv);
//    bool hasCompoundCollider(std::shared_ptr<CollisionComponent> collisionComp);
//    void compoundCollide(std::shared_ptr<CollisionComponent> componentCompound,
//                                          std::shared_ptr<CollisionComponent> component);



private:
    static void aabBox(const Ray &ray, std::shared_ptr<CollisionComponent> &c);
    void collisionResponse(std::shared_ptr<CollisionComponent> &a, std::shared_ptr<CollisionComponent> &b, const glm::vec3 &mtv);
    static void floorCollision(float floor, std::shared_ptr<CollisionComponent> obj);
    static void ceilingCollision(float ceiling, std::shared_ptr<CollisionComponent> obj);
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<ContinuousCollisionSystem> m_continuousCollisionSystem;
};

#endif // COLLISIONSYSTEM_H
