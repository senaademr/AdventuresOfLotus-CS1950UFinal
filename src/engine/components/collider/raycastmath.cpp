#include "raycastmath.h"

#include "boxcollider.h"
#include "raycastresult.h"
#include "engine/util/transform.h"

//code adapted from
// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
RaycastResult RaycastMath::castRayBox(Ray &ray, BoxCollider* boxCollider){
    //std::cout << "casting ray to box" << std::endl;
    //std::cout << Util::rayToString(ray) << std::endl;

    QList<glm::vec3> bounds = getBounds(boxCollider);
    glm::vec3 origin = ray.getOrigin();
    glm::vec3 inverseDirection = ray.getInverseDirection();
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    glm::ivec3 sign = ray.getSign();
    tmin = (bounds.at(sign.x).x - origin.x) * inverseDirection.x;
    tmax = (bounds.at(1-sign.x).x - origin.x) * inverseDirection.x;
    tymin = (bounds.at(sign.y).y - origin.y) * inverseDirection.y;
    tymax = (bounds.at(1-sign.y).y - origin.y) * inverseDirection.y;

    //std::cout << "tmin: " << tmin << "  tmax: " << tmax << "  tymin: " << tymin << "  tymax: " << tymax << std::endl;

    if((tmin > tymax) || (tymin > tmax)){
        return RaycastResult();
    }
    if(tymin > tmin){
        tmin = tymin;
    }
    if(tymax < tmax){
        tmax = tymax;
    }

    tzmin = (bounds.at(sign.z).z - origin.z) * inverseDirection.z;
    tzmax = (bounds.at(1-sign.z).z - origin.z) * inverseDirection.z;
    if((tmin > tzmax) || (tzmin > tmax)){
        return RaycastResult();
    }
    if(tzmin > tmin){
        tmin = tzmin;
    }
    if(tzmax < tmax){
        tmax = tzmax;
    }

    return RaycastResult(tmin);
}

RaycastResult RaycastMath::castRaySphere(Ray &ray, SphereCollider* sphereCollider){
    //unimplemented
    return RaycastResult();

}

RaycastResult RaycastMath::castRayCylinder(Ray &ray, CylinderCollider* cylinderCollider){
    //unimplemented
    return RaycastResult();

}

RaycastResult RaycastMath::castRayCompound(Ray &ray, CompoundCollider* compoundCollider){
    //unimplemented
    return RaycastResult();

}


//TODO WHYYYYY
QList<glm::vec3> RaycastMath::getBounds(BoxCollider* boxCollider){
    QList<glm::vec3> bounds;
    Transform transform = boxCollider->getTransform();
    glm::vec3 position = transform.getPosition();
    glm::vec3 size = transform.getSize();

    glm::vec3 boundsMin = position + -.5f * size;
    glm::vec3 boundsMax = position + .5f * size;
    boundsMin = glm::vec3(boundsMin.x, boundsMin.y, boundsMin.z);
    boundsMax = glm::vec3(boundsMax.x, boundsMax.y, boundsMax.z);
    bounds.append(boundsMin);
    bounds.append(boundsMax);


    assert(bounds.size() == 2);
    return bounds;
}
