#ifndef ENEMYMOVECOMPONENT_H
#define ENEMYMOVECOMPONENT_H

#include "engine/components/component.h"
#include "engine/components/tickable.h"
#include <map>

class TransformComponent;
class NavigationMesh;
class TickTimer;

class EnemyMoveComponent : public Component, public Tickable
{
public:
    EnemyMoveComponent(std::shared_ptr<TransformComponent> playerTransform, std::shared_ptr<NavigationMesh> navmesh, std::string enemyName);

    // Tickable interface
public:
    void tick(float seconds);
//    float VELOCITY = 7.f;

private:
    glm::vec3 getDirectionOfPathTowardPoint(glm::vec3 point);
    void attack();
    void die();
    void loadAnimationIndices();

private:
    std::shared_ptr<TransformComponent> m_playerTransform;
    std::shared_ptr<NavigationMesh> m_navmesh;
    std::string m_enemyType;
    // 0-idle, 1-move, 2-attack, 3-death
    std::shared_ptr<TickTimer> m_tickTimer;
    glm::vec4 m_indices;
};

#endif // ENEMYMOVECOMPONENT_H
