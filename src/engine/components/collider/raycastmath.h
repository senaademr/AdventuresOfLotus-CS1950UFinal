#ifndef RAYCASTMATH_H
#define RAYCASTMATH_H

#include "ray.h"
#include "engine/util/CommonIncludes.h"
#include "raycastresult.h"
#include <QList>

class BoxCollider;
class SphereCollider;
class CylinderCollider;
class CompoundCollider;


class RaycastMath
{
public:
    static RaycastResult castRayBox(Ray &ray, BoxCollider* boxCollider);
    static RaycastResult castRaySphere(Ray &ray, SphereCollider* sphereCollider);
    static RaycastResult castRayCylinder(Ray &ray, CylinderCollider* cylinderCollider);
    static RaycastResult castRayCompound(Ray &ray, CompoundCollider* compoundCollider);


    static QList<glm::vec3> getBounds(BoxCollider* boxCollider);
};

#endif // RAYCASTMATH_H
