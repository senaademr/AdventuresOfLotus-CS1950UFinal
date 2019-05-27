#include "collisioncomponent.h"
#include "engine/basics/gameobject.h"
#include "engine/systems/collisionsystem.h"
#include "engine/components/transformcomponent.h"
#include "engine/components/collider/collisionresponse.h"
#include "engine/components/collisionresponsecomponent.h"
#include "engine/collisionutils/ray.h"
#include "engine/collisionutils/aabbox.h"
#include "engine/collisionutils/floor.h"
#include "engine/collisionutils/collisionshape.h"

CollisionComponent::CollisionComponent() :
    Component(),
    m_currentFloorY(-100),
    m_floors()
{

}

CollisionComponent::~CollisionComponent()
{

}

float CollisionComponent::currentFloorY()
{
    return m_currentFloorY;
}

void CollisionComponent::addFloor(Floor floor)
{
    if (floor.height <= m_currentFloorY)
    {
        return;
    }
    if (onTopOfFloor(floor))
    {
        m_floors.push(floor);
        m_currentFloorY = floor.height;
    }
}

Floor CollisionComponent::floor() const
{
    std::shared_ptr<TransformComponent> transformComponent = m_gameObject->getComponent<TransformComponent>();
    if (collisionShape() == CollisionShape::CYLINDER) // use Circle floor
    {
        glm::vec3 center = transformComponent->getCenter(CollisionShape::CYLINDER);
        glm::vec2 circleC = glm::vec2(center.x, center.z);
        return Floor(Floor::Type::Circle, transformComponent->getBottom(CollisionShape::CYLINDER).y + transformComponent->getHeight(),
                     circleC, transformComponent->getRadius());
    }
    // otherwise use Rectangle floor
    glm::vec3 dimension = transformComponent->getSize();
    glm::vec3 pos = transformComponent->getBottom(CollisionShape::CYLINDER);
    // 2D - xzplane square
    Interval width{}, height{};
    rectangleInterval(width, height, glm::vec2(pos.x, pos.z), dimension.x / 2.f,  dimension.z / 2.f);
    return Floor(Floor::Type::Rectangle, pos.y + transformComponent->getHeight(), width, height);
}

bool CollisionComponent::onTopOfFloor(const Floor &floor)
{
    if (!floor.hasBound)
    {
        return true;
    }
    std::shared_ptr<TransformComponent> transformComponent = m_gameObject->getComponent<TransformComponent>();

    glm::vec2 mtv(0.f);
    if (floor.type == Floor::Type::Rectangle)
    {
        if (collisionShape() == CollisionShape::CYLINDER)
        {
            glm::vec3 center = transformComponent->getCenter(CollisionShape::CYLINDER);
            glm::vec2 circleC = glm::vec2(center.x, center.z);
            float radius = transformComponent->getRadius();
            mtv = rectangleCircle(floor.xBound, floor.yBound, circleC, radius);
        } else if (collisionShape() == CollisionShape::SPHERE) {
            glm::vec3 center = transformComponent->getCenter(CollisionShape::SPHERE);
            glm::vec2 circleC = glm::vec2(center.x, center.z);
            float radius = transformComponent->getRadius();
            mtv = rectangleCircle(floor.xBound, floor.yBound, circleC, radius * 0.1f);
        } else if (collisionShape() == CollisionShape::BOX) {
            glm::vec3 dimension = transformComponent->getSize();
            glm::vec3 pos = transformComponent->getBottom(CollisionShape::BOX);
            // 2D - xzplane square
            Interval width{}, height{};
            rectangleInterval(width, height, glm::vec2(pos.x, pos.z), dimension.x / 2.f,  dimension.z / 2.f);
            mtv = rectangleRectangle(width, height, floor.xBound, floor.yBound);
        }
    } else if (floor.type == Floor::Type::Circle) {
        if (collisionShape() == CollisionShape::CYLINDER)
        {
            glm::vec3 center = transformComponent->getCenter(CollisionShape::CYLINDER);
            glm::vec2 circleC = glm::vec2(center.x, center.z);
            float radius = transformComponent->getRadius();
            mtv = circleCircle(floor.center, floor.radius, circleC, radius);
        } else if (collisionShape() == CollisionShape::SPHERE) {
            glm::vec3 center = transformComponent->getCenter(CollisionShape::SPHERE);
            glm::vec2 circleC = glm::vec2(center.x, center.z);
            float radius = transformComponent->getRadius();
            mtv = circleCircle(floor.center, floor.radius, circleC, radius * 0.1f);
        } else if (collisionShape() == CollisionShape::BOX) {
            glm::vec3 dimension = transformComponent->getSize();
            glm::vec3 pos = transformComponent->getBottom(CollisionShape::BOX);
            // 2D - xzplane square
            Interval width{}, height{};
            rectangleInterval(width, height, glm::vec2(pos.x, pos.z), dimension.x / 2.f,  dimension.z / 2.f);
            mtv = rectangleCircle(width, height, floor.center, floor.radius);
        }
    }
    return glm::length2(mtv) > 0.f;
}

void CollisionComponent::collideFloor()
{
    while (m_floors.size() > 0 && !onTopOfFloor(m_floors.top()))
    {
        m_floors.pop();
    }
    if (m_floors.size() == 0)
    {
        m_currentFloorY = -100;
        return;
    }
    m_currentFloorY = m_floors.top().height;
    std::shared_ptr<TransformComponent> transformComponent = m_gameObject->getComponent<TransformComponent>();
    glm::vec3 bottom = transformComponent->getBottom(collisionShape());
    if (bottom.y < m_currentFloorY)
    {
        std::cout << "collides with floor" << std::endl;
    }
    bottom.y = glm::max(bottom.y, m_currentFloorY);
    transformComponent->setBottom(bottom, collisionShape());
}

bool CollisionComponent::onTheFloor() const
{
    std::shared_ptr<TransformComponent> transformComponent = m_gameObject->getComponent<TransformComponent>();
    glm::vec3 bottom = transformComponent->getBottom(collisionShape());
    return bottom.y == m_currentFloorY;
}

bool CollisionComponent::aabBox(const Ray &ray, float &t) const
{
    if (collisionShape() != CollisionShape::BOX)
    {
        return false;
    }
    std::shared_ptr<TransformComponent> transformComponent = m_gameObject->getComponent<TransformComponent>();
    glm::vec3 bottom = transformComponent->getBottom(CollisionShape::BOX);
    glm::vec3 dimension = transformComponent->getSize();
    float halfX = dimension.x / 2.f;
    float halfZ = dimension.z / 2.f;
    std::unique_ptr<AABBox> aabBox = std::make_unique<AABBox>(glm::vec3(bottom.x - halfX, bottom.y, bottom.z - halfZ),
                                                              glm::vec3(bottom.x + halfX, bottom.y + dimension.y, bottom.z + halfZ));
    return aabBox->intersect(ray, t);
}
// MTV - in the direction of other box
glm::vec3 CollisionComponent::boxBox(const glm::vec3 &pos, const glm::vec3 &dimension,
                                            const glm::vec3 &otherPos, const glm::vec3 &otherDimension)
{
    // 2D - xzplane square
    Interval width{}, height{};
    rectangleInterval(width, height, glm::vec2(pos.x, pos.z), dimension.x / 2.f,  dimension.z / 2.f);
    Interval otherWidth{}, otherHeight{};
    rectangleInterval(otherWidth, otherHeight, glm::vec2(otherPos.x, otherPos.z), otherDimension.x / 2.f,  otherDimension.z / 2.f);

    float xMtv = intervalMTV(otherWidth, width);
    if (xMtv == 0) // no collision in x line
    {
        return glm::vec3(0);
    }
    float zMtv = intervalMTV(otherHeight, height);
    if (zMtv == 0) // no collision in z line
    {
        return glm::vec3(0);
    }
    // 1D - y line
    float yMtv = intervalMTV(Interval{otherPos.y, otherPos.y+otherDimension.y}, Interval{pos.y, pos.y+dimension.y});
    if (yMtv == 0) // no collision in y line
    {
        return glm::vec3(0);
    }
    // collide in x AND z AND y line
    // return shortest mtv
    glm::vec3 mtv_xDir = glm::vec3(xMtv, 0, 0);
    glm::vec3 mtv_zDir = glm::vec3(0, 0, zMtv);
    glm::vec3 mtv_yDir = glm::vec3(0, yMtv, 0);
    float xSquaredLength = glm::length2(mtv_xDir);
    float zSquaredLength = glm::length2(mtv_zDir);
    float ySquaredLength = glm::length2(mtv_yDir);
    if (xSquaredLength < zSquaredLength && xSquaredLength < ySquaredLength) // return x dir
    {
        return mtv_xDir;
    }
    else if (zSquaredLength < xSquaredLength && zSquaredLength < ySquaredLength) // return z dir
    {
        return mtv_zDir;
    }
    // return y dir
    return mtv_yDir;
}
// MTV - in the direction of rectangle b
glm::vec2 CollisionComponent::rectangleRectangle(const Interval &ax, const Interval &ay,
                                                 const Interval &bx, const Interval &by)
{
    float xMtv = intervalMTV(bx, ax);
    if (xMtv == 0) // no collision in x line
    {
        return glm::vec2(0);
    }
    float yMtv = intervalMTV(by, ay);
    if (yMtv == 0) // no collision in y line
    {
        return glm::vec2(0);
    }
    // return shortest mtv
    glm::vec2 mtv_xDir = glm::vec2(xMtv, 0);
    glm::vec2 mtv_yDir = glm::vec2(0, yMtv);
    float xSquaredLength = glm::length2(mtv_xDir);
    float ySquaredLength = glm::length2(mtv_yDir);
    if (xSquaredLength < ySquaredLength) // return x dir
    {
        return mtv_xDir;
    }
    // return y dir
    return mtv_yDir;
}
// MTV - in the direction of CYLINDER
glm::vec3 CollisionComponent::boxCylinder(const glm::vec3 &pos, const glm::vec3 &dimension,
                                                const glm::vec3 &otherPos, const float &otherRadius, const float &otherHeight)
{
    // 1D - y line
    float yMtv = intervalMTV(Interval{otherPos.y, otherPos.y+otherHeight}, Interval{pos.y, pos.y+dimension.y}); // in the direction of other cylinder
    if (yMtv == 0) // no collision in y line
    {
        return glm::vec3(0);
    }
    // 2D - xz plane
    Interval width{}, height{};
    rectangleInterval(width, height, glm::vec2(pos.x, pos.z), dimension.x / 2.f,  dimension.z / 2.f);
    glm::vec2 xzMtv = rectangleCircle(width, height, glm::vec2(otherPos.x, otherPos.z), otherRadius);
    if (glm::length2(xzMtv) == 0)
    {
        return glm::vec3(0);
    }
    // collide in xzplane AND y line
    // return shortest mtv - in the direction of other cylinder
    if (glm::length2(xzMtv) < yMtv*yMtv)
    {
        return glm::vec3(xzMtv.x, 0, xzMtv.y);
    }
    return glm::vec3(0, yMtv, 0);
}
// MTV - in the direction of sphere
glm::vec3 CollisionComponent::boxSphere(const glm::vec3 &pos, const glm::vec3 &dimension,
                                                const glm::vec3 &otherCenter, const float &otherRadius)
{
    Interval width{}, height{};
    rectangleInterval(width, height, glm::vec2(pos.x, pos.z), dimension.x / 2.f,  dimension.z / 2.f);
    glm::vec2 xzMtv = rectangleCircle(width, height, glm::vec2(otherCenter.x, otherCenter.z), otherRadius);

    if (glm::length2(xzMtv) == 0)
    {
        return glm::vec3(0);
    }
    Interval depth{pos.y, pos.y+dimension.y};
    glm::vec2 xyMtv = rectangleCircle(width, depth, glm::vec2(otherCenter.x, otherCenter.y), otherRadius);
    if (glm::length2(xyMtv) == 0)
    {
        return glm::vec3(0);
    }
    glm::vec2 yzMtv = rectangleCircle(depth, height, glm::vec2(otherCenter.y, otherCenter.z), otherRadius);
    if (glm::length2(yzMtv) == 0)
    {
        return glm::vec3(0);
    }
    float xzSquaredLength = glm::length2(xzMtv);
    float xySquaredLength = glm::length2(xyMtv);
    float yzSquaredLength = glm::length2(yzMtv);
    if (xzSquaredLength < xySquaredLength && xzSquaredLength < yzSquaredLength)
    {
        return glm::vec3(xzMtv.x, 0, xzMtv.y);
    } else if (xySquaredLength < xzSquaredLength && xySquaredLength < yzSquaredLength)
    {
        return glm::vec3(xyMtv.x, xyMtv.y, 0);
    }
    return glm::vec3(0, yzMtv.x, yzMtv.y);
}
// MTV - in the direction of sphere
glm::vec3 CollisionComponent::cylinderSphere(const glm::vec3 &pos, const float &radius, const float &height,
                                const glm::vec3 &otherCenter, const float &otherRadius)
{
    // 2D - xzplane circle
    glm::vec2 circlePos = glm::vec2(pos.x, pos.z);
    glm::vec2 circleOtherPos = glm::vec2(otherCenter.x, otherCenter.z);
    glm::vec2 xzMtv = circleCircle(circleOtherPos, otherRadius, circlePos, radius);
    if (glm::length2(xzMtv) == 0)
    {
        return glm::vec3(0);
    }
    // xy plane - rectangle circle
    glm::vec2 xyMtv = rectangleCircle(Interval{pos.x-radius, pos.x+radius}, Interval{pos.y, pos.y+height}, glm::vec2(otherCenter.x, otherCenter.y), otherRadius);
    if (glm::length2(xyMtv) == 0)
    {
        return glm::vec3(0);
    }
    // yz plane
    glm::vec2 yzMtv = rectangleCircle(Interval{pos.y, pos.y+height}, Interval{pos.z-radius, pos.z+radius}, glm::vec2(otherCenter.y, otherCenter.z), otherRadius);
    if (glm::length2(yzMtv) == 0)
    {
        return glm::vec3(0);
    }
    float xzSquaredLength = glm::length2(xzMtv);
    float xySquaredLength = glm::length2(xyMtv);
    float yzSquaredLength = glm::length2(yzMtv);
    if (xzSquaredLength < xySquaredLength && xzSquaredLength < yzSquaredLength)
    {
        return glm::vec3(xzMtv.x, 0, xzMtv.y);
    } else if (xySquaredLength < xzSquaredLength && xySquaredLength < yzSquaredLength)
    {
        return glm::vec3(xyMtv.x, xyMtv.y, 0);
    }
    return glm::vec3(0, yzMtv.x, yzMtv.y);
}
// MTV - in the direction of other CollisionShape::CYLINDER
glm::vec3 CollisionComponent::cylinderCylinder(const glm::vec3 &pos, const float &radius, const float &height,
                                                      const glm::vec3 &otherPos, const float &otherRadius, const float &otherHeight)
{
    // 1D - y line
    float yMtv = intervalMTV(Interval{otherPos.y, otherPos.y+otherHeight}, Interval{pos.y, pos.y+height}); // in the direction of other cylinder
    if (yMtv == 0) // no collision in y line
    {
        return glm::vec3(0);
    }
    // 2D - xzplane circle
    glm::vec2 circlePos = glm::vec2(pos.x, pos.z);
    glm::vec2 circleOtherPos = glm::vec2(otherPos.x, otherPos.z);
    glm::vec2 xzMtv = circleCircle(circleOtherPos, otherRadius, circlePos, radius);
    if (glm::length2(xzMtv) == 0)
    {
        return glm::vec3(0);
    }
    // collide in xzplane AND y line
    // return shortest mtv - in the direction of other cylinder
    if (glm::length2(xzMtv) < yMtv*yMtv)
    {
        return glm::vec3(xzMtv.x, 0, xzMtv.y);
    }
    return glm::vec3(0, yMtv, 0);
}
// MTV - in the direction of other sphere
glm::vec3 CollisionComponent::sphereSphere(const glm::vec3 &center, const float &radius, const glm::vec3 &otherCenter, const float &otherRadius)
{
    float squaredDistance = glm::distance2(center, otherCenter);
    if (squaredDistance >= (radius+otherRadius)*(radius+otherRadius)) // no collision
    {
        return glm::vec3(0);
    }
    if (squaredDistance == 0.f) {
        return otherCenter - center;
    }
    float len = glm::sqrt(squaredDistance);
    glm::vec3 mtv = ((otherCenter - center) / len) * (radius + otherRadius - len);
    if (mtv.y != 0) // cast y to x and z direction
    {
        mtv.x = glm::length(glm::vec2(mtv.x, mtv.y));
        mtv.z = glm::length(glm::vec2(mtv.z, mtv.y));
        mtv.y = 0;
    }
    return mtv;
}
 //MTV - in the direction of a
float CollisionComponent::intervalMTV(const Interval &a, const Interval &b)
{
    float aRight = b.max - a.min;
    float aLeft = a.max - b.min;
    if (aLeft < 0 || aRight < 0)
        return 0; // no overlap
    if (aRight < aLeft)
        return aRight;
    else
        return -aLeft;
}
// MTV - in the direction of circle
glm::vec2 CollisionComponent::rectangleCircle(const Interval &ax, const Interval &ay, const glm::vec2 &c, const float &r)
{
    glm::vec2 closestPoint = glm::clamp(c, glm::vec2(ax.min, ay.min), glm::vec2(ax.max, ay.max));
    float squaredDistance = glm::distance2(c, closestPoint);
    if (squaredDistance > r*r) // no collision
    {
        return glm::vec2(0);
    }
    float xMtv = intervalMTV(Interval{c.x-r, c.x+r}, ax);
    float yMtv = intervalMTV(Interval{c.y-r, c.y+r}, ay);
    glm::vec2 mtv_xDir = glm::vec2(xMtv, 0);
    glm::vec2 mtv_yDir = glm::vec2(0, yMtv);
    if (glm::length2(mtv_xDir) < glm::length2(mtv_yDir))
    {
        return mtv_xDir;
    }
    return mtv_yDir;
}
// MTV - in the direction of circle a
glm::vec2 CollisionComponent::circleCircle(const glm::vec2 &ac, const float &ar, const glm::vec2 &bc, const float &br)
{
    float squaredDistance = glm::distance2(ac, bc);
    if (squaredDistance >= (ar+br)*(ar+br)) // no collision
    {
        return glm::vec2(0);
    }
    if (squaredDistance == 0.f) {
        return ac - bc;
    }
    float len = glm::sqrt(squaredDistance);
    return ((ac - bc) / len) * (ar + br - len);
}

void CollisionComponent::rectangleInterval(Interval &width, Interval &height, const glm::vec2 &center,
                                                       const float &halfWidth, const float &halfHeight)
{
    width = Interval{center.x - halfWidth, center.x + halfWidth};
    height = Interval{center.y - halfHeight, center.y + halfHeight};
}
