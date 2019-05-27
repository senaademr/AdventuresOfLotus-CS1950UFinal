#ifndef COLLIDERMATH_H
#define COLLIDERMATH_H

#include "collider.h"
#include <QList>

class TransformComponent;
class Transform;

class ColliderMath
{
public:

    enum class DIMENSION{
        X,
        Y,
        Z
    };
    //actual collisions
public:
    static CollisionResponse collideCylinderCylinder(CylinderCollider* collider1, CylinderCollider* collider2);
    static CollisionResponse collideCylinderBox(CylinderCollider *cylinderCollider, BoxCollider *boxCollider);
    static CollisionResponse collideCylinderSphere(CylinderCollider *cylinderCollider, SphereCollider * sphereCollider);

    static CollisionResponse collideBoxSphere(BoxCollider* boxCollider, SphereCollider* sphereCollider);
    static CollisionResponse collideBoxBox(BoxCollider* collider1, BoxCollider* collider2);

    static CollisionResponse collideSphereSphere(SphereCollider* collider1, SphereCollider* collider2);

    // dummy collisions
public:
    static CollisionResponse negateResponse(CollisionResponse response);
    static CollisionResponse collideSphereBox(SphereCollider* sphereCollider, BoxCollider* boxCollider);
    static CollisionResponse collideBoxCylinder(BoxCollider *boxCollider, CylinderCollider *cylinderCollider);
    static CollisionResponse collideSphereCylinder(SphereCollider * sphereCollider, CylinderCollider *cylinderCollider);

public:
    //line collisions
    static bool collideLineCylinder(Transform &transform1, Transform &transform2);
    static bool collideLineBox(Transform &transform1, Transform &transform2, DIMENSION dim);
    static bool collideLine(glm::vec2 range1, glm::vec2 range2);

    static glm::vec3 getLineMtvCylinder(Transform &transform1, Transform &transform2);

    static glm::vec3 getLineLineMtvBox(Transform &transform1, Transform &transform2, DIMENSION dim);
    static glm::vec3 getLineLineMtv(glm::vec2 range1, glm::vec2 range2, DIMENSION dim);

    static bool collideSpheres(Transform &transform1, Transform &transform2);

    static bool collideCylinderLineBox(Transform &transformCylinder, Transform &transformBox);

    static glm::vec3 getSphereSphereMtv(Transform &transform1, Transform &transform2);


    static bool collideCircles(Transform &transform1, Transform &transform2);

    static bool collidePointSphere(Transform &transformSphere, glm::vec3 point);
    static bool collidePointCircle(Transform &transformCylinder, glm::vec2 point);

    //mtv

    static glm::vec3 getCircleCircleMtv(Transform &transform1, Transform &transform2);

    static glm::vec3 getPointCircleMtv(Transform &transformCylinder,Transform &transformBox);
    static glm::vec3 getPointSphereMtv(Transform &transformSphere, glm::vec3 point);

    //helpers


    static glm::vec3 clampPoint(Transform &transformBox, Transform &transformSphere);


    static glm::vec2 clampPointXZ(Transform &transformBox,Transform &transformCylinder);

    static float clampDimension(Transform &transformBox,Transform &transformSphere, DIMENSION dim);

    static float getRadius(glm::vec3 size);
    static glm::vec2 toCircle(glm::vec3 pos);


    static glm::vec2 getRangeCylinder(Transform &transformCylinder);
    static glm::vec2 getRangeBox(Transform &transformBox, DIMENSION dim);
    static glm::vec2 getRangeBox(float pos, float size);

    static glm::vec3 getSmallerMtv(glm::vec3 mtv1, glm::vec3 mtv2);
    static glm::vec3 getSmallerMtv(glm::vec3 mtv1, glm::vec3 mtv2, glm::vec3 mtv3);



};

#endif // COLLIDERMATH_H
