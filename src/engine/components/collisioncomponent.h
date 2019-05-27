#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "engine/components/component.h"
#include "engine/collisionutils/floor.h"
#include <stack>

//struct Floor;
struct Ray;
struct Interval;
enum class CollisionShape;
class CollisionComponent : public Component
{
public:
    CollisionComponent();
    virtual ~CollisionComponent() override;
    virtual CollisionShape collisionShape() const = 0;
    virtual bool movable() const = 0;
    virtual glm::vec3 customCollision(std::shared_ptr<CollisionComponent> other) const {return glm::vec3(0);}
    virtual bool hasFloor() const {return false;}
    virtual Floor floor() const;
    float currentFloorY();
    void setCurrentYFloor(float currentFloorY);
    void addFloor(Floor floor);
    bool onTopOfFloor(const Floor &floor);
    void collideFloor();
    bool onTheFloor() const;
    bool aabBox(const Ray &ray, float &t) const;

    static glm::vec3 boxBox(const glm::vec3 &pos, const glm::vec3 &dimension,
                            const glm::vec3 &otherPos, const glm::vec3 &otherDimension);
    static glm::vec2 rectangleRectangle(const Interval &ax, const Interval &ay,
                                                     const Interval &bx, const Interval &by);
    static glm::vec3 boxCylinder(const glm::vec3 &pos, const glm::vec3 &dimension,
                                 const glm::vec3 &otherPos, const float &otherRadius, const float &otherHeight);
    static glm::vec3 boxSphere(const glm::vec3 &pos, const glm::vec3 &dimension,
                               const glm::vec3 &otherCenter, const float &otherRadius);
    static glm::vec3 cylinderSphere(const glm::vec3 &pos, const float &radius, const float &height,
                                    const glm::vec3 &otherCenter, const float &otherRadius);
    static glm::vec3 cylinderCylinder(const glm::vec3 &pos, const float &radius, const float &height,
            const glm::vec3 &otherPos, const float &otherRadius, const float &otherHeight);
    static glm::vec3 sphereSphere(const glm::vec3 &center, const float &radius, const glm::vec3 &otherCenter, const float &otherRadius);
    static float intervalMTV(const Interval &a, const Interval &b); // MTV - in the direction of a
    static glm::vec2 rectangleCircle(const Interval &ax, const Interval &ay, const glm::vec2 &c, const float &r); // MTV - in the direction of circle
    static glm::vec2 circleCircle(const glm::vec2 &ac, const float &ar, const glm::vec2 &bc, const float &br); // MTV - in the direction of circle a
    static void rectangleInterval(Interval &width, Interval &height, const glm::vec2 &center, const float &halfWidth, const float &halfHeight);

private:
    float m_currentFloorY;
    std::stack<Floor> m_floors;
};

#endif // COLLISIONCOMPONENT_H
