#include "collidermath.h"

#include "cylindercollider.h"
#include "spherecollider.h"
#include "boxcollider.h"
#include "compoundcollider.h"

#include "engine/components/transformcomponent.h"
#include "engine/components/physicscomponent.h"
#include "engine/components/collisioncomponent.h"
#include "engine/basics/gameobject.h"
#include "engine/util/CommonIncludes.h"
#include "collisionresponse.h"


/*****************************Actual Collisions ***************************/

CollisionResponse ColliderMath::collideCylinderCylinder(CylinderCollider* collider1, CylinderCollider* collider2){
    Transform transform1 = collider1->getTransform();
    Transform transform2 = collider2->getTransform();

    //std::cout << "testing cylinder collide with cylinder" << std::endl;
    bool areColliding = collideLineCylinder(transform1, transform2) && collideCircles(transform1, transform2);
    if(areColliding){
        glm::vec3 circleMtv = getCircleCircleMtv(transform1, transform2);
        glm::vec3 lineMtv = getLineMtvCylinder(transform1, transform2);
        glm::vec3 mtv = getSmallerMtv(circleMtv, lineMtv);
        return CollisionResponse(mtv);
        //ColliderMath::resolveMtv(collider1, collider2, circleMtv, lineMtv);
    }
    return CollisionResponse();
}

CollisionResponse ColliderMath::collideCylinderBox(CylinderCollider *cylinderCollider, BoxCollider *boxCollider){
    Transform transformCylinder = cylinderCollider->getTransform();
    Transform transformBox = boxCollider->getTransform();

    glm::vec2 clampedPoint = clampPointXZ(transformBox, transformCylinder);
    bool colliding = collideCylinderLineBox(transformCylinder, transformBox)
            && collidePointCircle(transformCylinder, clampedPoint);
    if(colliding){
        glm::vec2 cylinderRangeY = getRangeCylinder(transformCylinder);
        glm::vec2 boxRangeY = getRangeBox(transformBox, DIMENSION::Y);
        glm::vec3 lineMtv = getLineLineMtv(cylinderRangeY, boxRangeY, DIMENSION::Y);

        glm::vec3 circleMtv = getPointCircleMtv(transformCylinder, transformBox);
        //std::cout << "lineMtv: " << lineMtv << "  circleMtv: " << circleMtv << std::endl;
        glm::vec3 mtv = getSmallerMtv(lineMtv, circleMtv);
        return CollisionResponse(mtv);
    }
    return CollisionResponse();
}

CollisionResponse ColliderMath::collideCylinderSphere(CylinderCollider *cylinderCollider, SphereCollider * sphereCollider){
    //std::cout << "unimplemented collision: cylinder sphere" << std::endl;
    return CollisionResponse();
}

CollisionResponse ColliderMath::collideBoxBox(BoxCollider* collider1, BoxCollider* collider2){
    Transform transform1 = collider1->getTransform();
    Transform transform2 = collider2->getTransform();

    bool collideX = collideLineBox(transform1, transform2, DIMENSION::X);
    bool collideY = collideLineBox(transform1, transform2, DIMENSION::Y);
    bool collideZ = collideLineBox(transform1, transform2, DIMENSION::Z);
    bool result = collideX && collideY && collideZ;
    if(result){
        glm::vec3 lineMtvX = getLineLineMtvBox(transform1, transform2, DIMENSION::X);
        glm::vec3 lineMtvY = getLineLineMtvBox(transform1, transform2, DIMENSION::Y);
        glm::vec3 lineMtvZ = getLineLineMtvBox(transform1, transform2, DIMENSION::Z);
        //resolveMtv(collider1, collider2, lineMtvX, lineMtvY, lineMtvZ);
        glm::vec3 mtv = getSmallerMtv(lineMtvX, lineMtvY, lineMtvZ);
        return CollisionResponse(mtv);
    }
    return CollisionResponse();
}

CollisionResponse ColliderMath::collideBoxSphere(BoxCollider* boxCollider, SphereCollider* sphereCollider){
    Transform transformBox = boxCollider->getTransform();
    Transform transformSphere = sphereCollider->getTransform();
    glm::vec3 clampedPoint = clampPoint(transformBox, transformSphere);
    bool colliding = collidePointSphere(transformSphere, clampedPoint);
    if(colliding){
        glm::vec3 mtv = getPointSphereMtv(transformSphere, clampedPoint);
        return CollisionResponse(mtv);
    }
    return CollisionResponse();
}

CollisionResponse ColliderMath::collideSphereSphere(SphereCollider* collider1, SphereCollider* collider2){
    Transform transform1 = collider1->getTransform();
    Transform transform2 = collider2->getTransform();
    bool colliding = collideSpheres(transform1, transform2);
    if(colliding){
        glm::vec3 mtv = getSphereSphereMtv(transform1, transform2);
        return CollisionResponse(mtv);
    }
    return CollisionResponse();
}

/*************************** dummy collisions *****************/

CollisionResponse ColliderMath::negateResponse(CollisionResponse response){
    if(response.didCollide){
        return CollisionResponse(-1.f *response.mtv);
    }
    return response;
}

CollisionResponse ColliderMath::collideSphereBox(SphereCollider* sphereCollider, BoxCollider* boxCollider){
    return negateResponse(collideBoxSphere(boxCollider, sphereCollider));

}

CollisionResponse ColliderMath::collideBoxCylinder(BoxCollider *boxCollider, CylinderCollider *cylinderCollider){
    return negateResponse(collideCylinderBox(cylinderCollider, boxCollider));
}

CollisionResponse ColliderMath::collideSphereCylinder(SphereCollider * sphereCollider, CylinderCollider *cylinderCollider){
    return negateResponse(collideCylinderSphere(cylinderCollider, sphereCollider));
}




/***************************** Line collisions ***************************/

bool ColliderMath::collideLineCylinder(Transform &transform1, Transform &transform2)
{
    glm::vec2 range1 = ColliderMath::getRangeCylinder(transform1);
    glm::vec2 range2 = ColliderMath::getRangeCylinder(transform2);
    return collideLine(range1, range2);
}

bool ColliderMath::collideLine(glm::vec2 range1, glm::vec2 range2){
    bool  result= (range1.x < range2.y && range2.x < range1.y);
    return result;
}

bool ColliderMath::collideLineBox(Transform &transform1, Transform &transform2, DIMENSION dim){
    glm::vec2 range1 = getRangeBox(transform1, dim);
    glm::vec2 range2 = getRangeBox(transform2, dim);
    return collideLine(range1, range2);
}





bool ColliderMath::collideSpheres(Transform &transform1, Transform &transform2){
    float distance2 = glm::distance2(transform1.getPosition(), transform2.getPosition());
    float radius1 = getRadius(transform1.getSize());
    float radius2 = getRadius(transform2.getSize());
    bool result = distance2 < powf(radius1 + radius2, 2);
    return result;
}

glm::vec3 ColliderMath::getSphereSphereMtv(Transform &transform1, Transform &transform2){
    glm::vec3 locationDifference = transform1.getPosition()-transform2.getPosition();
    float distance = glm::length(locationDifference);

    glm::vec3 direction = glm::normalize(locationDifference);
    float radius1 = getRadius(transform1.getSize());
    float radius2 = getRadius(transform2.getSize());
    glm::vec3 mtv = (distance -radius1 - radius2 )*direction;
    return mtv;

}




bool ColliderMath::collideCylinderLineBox(Transform &transformCylinder, Transform &transformBox){
    glm::vec2 yRangeCylinder = getRangeCylinder(transformCylinder);
    glm::vec2 yRangeBox = getRangeBox(transformBox, DIMENSION::Y);
    return collideLine(yRangeCylinder, yRangeBox);

}


glm::vec3 ColliderMath::getCircleCircleMtv(Transform &transform1, Transform &transform2){
    glm::vec2 circlePos1 = toCircle(transform1.getPosition());
    glm::vec2 circlePos2 = toCircle(transform2.getPosition());
    float length = glm::distance(circlePos1, circlePos2);
    float radius1 = getRadius(transform1.getSize());
    float radius2 = getRadius(transform2.getSize());
    glm::vec2 mtv2d = (circlePos2-circlePos1);
    mtv2d /= length;
    mtv2d *= (radius1 + radius2-length);
    glm::vec3 mtv = glm::vec3(mtv2d.x, 0, mtv2d.y);
    return mtv;
}

glm::vec3 ColliderMath::getLineMtvCylinder(Transform &transform1, Transform &transform2){
    glm::vec2 yRange1 = ColliderMath::getRangeCylinder(transform1);
    glm::vec2 yRange2 = ColliderMath::getRangeCylinder(transform2);

    return getLineLineMtv(yRange1, yRange2, DIMENSION::Y);

}

glm::vec3 ColliderMath::getLineLineMtvBox(Transform &transform1, Transform &transform2, DIMENSION dim){
    glm::vec2 range1 = ColliderMath::getRangeBox(transform1, dim);
    glm::vec2 range2 = ColliderMath::getRangeBox(transform2, dim);
    return getLineLineMtv(range1, range2, dim);
}

glm::vec3 ColliderMath::getLineLineMtv(glm::vec2 range1, glm::vec2 range2, DIMENSION dim){
    float aRight = range2.y - range1.x;
    float aLeft = range1.y - range2.x;
    float value = 1;
    if(aLeft < 0 || aRight < 0){
        std::cout << "error? " << std::endl;
    }
    if(aRight < aLeft){
        value = -aRight;
    }
    else{
        value = aLeft;
    }
    switch(dim){
        case(DIMENSION::X):
            return glm::vec3(value, 0, 0);
        case(DIMENSION::Y):
            return glm::vec3(0, value, 0);
        case(DIMENSION::Z):
            return glm::vec3(0, 0, value);
    }
    assert(false);
    return glm::vec3(0);
}





bool ColliderMath::collideCircles(Transform &transform1, Transform &transform2){
    glm::vec2 circlePos1 = toCircle(transform1.getPosition());
    glm::vec2 circlePos2 = toCircle(transform2.getPosition());

    float distance2 = glm::distance2(circlePos1, circlePos2);
    float radius1 = getRadius(transform1.getSize());
    float radius2 = getRadius(transform2.getSize());
    bool result = distance2 < powf(radius1 + radius2, 2);
    if(result){
    }
    return result;

}


glm::vec3 ColliderMath::getPointSphereMtv(Transform &transformSphere, glm::vec3 point){
    float radius = getRadius(transformSphere.getSize());
    glm::vec3 mtv = transformSphere.getPosition()- point;
    float size = glm::length(mtv);
    mtv = glm::normalize(mtv);
    mtv = (radius - size)*mtv;
    return mtv;
}

//if inside, find the dimension that is shortest
//TODO FIXXXXXXXX
glm::vec3 ColliderMath::getPointCircleMtv(Transform &transformCylinder,Transform &transformBox){
    glm::vec2 point = clampPointXZ(transformBox, transformCylinder);
    float radius = getRadius(transformCylinder.getSize());
    glm::vec2 circle = toCircle(transformCylinder.getPosition());

    glm::vec2 mtv =  circle - point;
    float size = glm::length(mtv);
    if(size==0){
        glm::vec2 xRange = getRangeBox(transformBox, DIMENSION::X);
        glm::vec2 zRange = getRangeBox(transformBox, DIMENSION::Z);
        glm::vec3 mtvX1 = glm::vec3(circle.x - xRange.x, 0, 0 );
        glm::vec3 mtvX2 = glm::vec3(circle.x - xRange.y, 0, 0 );
        glm::vec3 mtvX = getSmallerMtv(mtvX1, mtvX2);
        //std::cout << "circleX: " << circle.x << "  xRange: " << xRange << std::endl;
        //std::cout << "mtvX " <<mtvX << std::endl;

        glm::vec3 mtvY1 = glm::vec3(0, 0, circle.y - zRange.x);
        glm::vec3 mtvY2 = glm::vec3(0, 0, circle.y - zRange.y);
        glm::vec3 mtvY = getSmallerMtv(mtvY1, mtvY2);

        glm::vec3 mtv = getSmallerMtv(mtvX, mtvY);
        float newSize = glm::length(mtv);
        return glm::normalize(mtv)* (radius + newSize);
        //float toXMin = glm::distance(circle.x, xRange.x);

        //return glm::vec3(100000);
    }
    else{
        mtv = glm::normalize(mtv);
        mtv = (size - radius)*mtv;
        return glm::vec3(mtv.x, 0, mtv.y);
    }

}

bool ColliderMath::collidePointSphere(Transform &transformSphere, glm::vec3 point){
    float radius = getRadius(transformSphere.getSize());
    float distance = glm::distance(transformSphere.getPosition(), point);
    return  distance <= radius;
}

bool ColliderMath::collidePointCircle(Transform &transformCylinder, glm::vec2 point){
    glm::vec2 circle = toCircle(transformCylinder.getPosition());
    float radius = getRadius(transformCylinder.getSize());
    return glm::distance(circle, point) <= radius;
}

/***************************  Helper *****************************/

float ColliderMath::getRadius(glm::vec3 size){
    return std::abs(size.x/2.f);
}

glm::vec2 ColliderMath::toCircle(glm::vec3 pos){
    return glm::vec2(pos.x, pos.z);
}


glm::vec3 ColliderMath::clampPoint(Transform &transformBox, Transform &transformSphere){
    float x = clampDimension(transformBox, transformSphere, DIMENSION::X);
    float y = clampDimension(transformBox, transformSphere, DIMENSION::Y);
    float z = clampDimension(transformBox, transformSphere, DIMENSION::Z);
    glm::vec3 clampedPoint = glm::vec3(x,y,z);
    return clampedPoint;

}

glm::vec2 ColliderMath::clampPointXZ(Transform &transformBox,Transform &transformCylinder){
    float x = clampDimension(transformBox, transformCylinder, DIMENSION::X);
    float z = clampDimension(transformBox, transformCylinder, DIMENSION::Z);
    glm::vec2 clampedPoint =  glm::vec2(x, z);
    return clampedPoint;

}

float ColliderMath::clampDimension(Transform &transformBox,Transform &transformSphere, DIMENSION dim){
    glm::vec2 range = getRangeBox(transformBox, dim);
    glm::vec3 pos = transformSphere.getPosition();
    switch(dim){
        case(DIMENSION::X):
            return glm::clamp(pos.x, range.x, range.y);
        case(DIMENSION::Y):
            return glm::clamp(pos.y, range.x, range.y);
        case(DIMENSION::Z):
            return glm::clamp(pos.z, range.x, range.y);
    }
    assert(false);
    return -1;
}

/**
 * @brief ColliderMath::getRangeCylinder
 * Returns a vec2 representing the vertical dimension of the cylinder.
 * This is different from the box range because the starting point of the cylinder is the bottom
 * @param transformComponent
 * @return
 */
glm::vec2 ColliderMath::getRangeCylinder(Transform &transformCylinder){
    glm::vec3 pos = transformCylinder.getPosition();
    glm::vec3 size = transformCylinder.getSize();
    return glm::vec2(pos.y, pos.y + size.y);

}

/**
 * @brief ColliderMath::getRangeBox
 * Returns a vec2 representing a dimension of a box.
 * This is different from the cylinder range because the starting point of a box is the center
 * @param transformComponent
 * @param dim
 * @return
 */
glm::vec2 ColliderMath::getRangeBox(Transform &transformBox, DIMENSION dim){
    glm::vec3 pos = transformBox.getPosition();
    glm::vec3 size = transformBox.getSize();
    switch(dim){
        case(DIMENSION::X):
            return getRangeBox(pos.x, size.x);
        case(DIMENSION::Y):
            return getRangeBox(pos.y, size.y);
        case(DIMENSION::Z):
            return getRangeBox(pos.z, size.z);
    }
    assert(false); //should never reach here
    return glm::vec2(0);

}

/**
 * @brief ColliderMath::getRangeBox
 * Returns a vec2 representing a dimension of a box.
 * This is different from the cylinder range because the starting point of a box is the center
 * @param pos
 * @param size
 * @return
 */
glm::vec2 ColliderMath::getRangeBox(float pos, float size){
    assert(size >= 0);
    return glm::vec2(pos-size/2.f, pos + size/2.f);
}

glm::vec3 ColliderMath::getSmallerMtv(glm::vec3 mtv1, glm::vec3 mtv2){
    if(glm::length2(mtv1) < glm::length2(mtv2)){
        return mtv1;
    }
    else{
        return mtv2;
    }
}

glm::vec3 ColliderMath::getSmallerMtv(glm::vec3 mtv1, glm::vec3 mtv2, glm::vec3 mtv3){
    float length1 = glm::length2(mtv1);
    float length2 = glm::length2(mtv2);
    float length3 = glm::length2(mtv3);
    if(length1 < length2 && length1 < length3){
        return mtv1;
    }
    else if(length2 < length3){
        return mtv2;
    }
    else{
        return mtv3;
    }
}
