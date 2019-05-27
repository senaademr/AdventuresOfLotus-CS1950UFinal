#ifndef ENEMYAIRESPONSECOMPONENT_H
#define ENEMYAIRESPONSECOMPONENT_H
#include "engine/components/airesponsecomponent.h"
#include <QList>
class PhysicsComponent;
class AnimationComponent;
class TransformComponent;
class NavigationMesh;
class EnemyAIResponseComponent : public AIResponseComponent
{
public:
    EnemyAIResponseComponent(std::shared_ptr<TransformComponent> targetTransform,
                             std::shared_ptr<NavigationMesh> navmesh,
                             std::string enemyType);
    ~EnemyAIResponseComponent() override;
    bool updatePathTarget();
    void makeNextMove(float seconds);
    void attackTarget(float seconds);
    void postAttackTarget() const;
    bool nearTarget() const;
    bool isDead() const;

private:
    const float rotationSpeed = 6.f;

    void setDesiredRotation(const glm::vec3 &direction);
    void loadAnimationIndices();


    // target transform to obtain target position information
    std::shared_ptr<TransformComponent> m_targetTransform;
    std::shared_ptr<NavigationMesh> m_navmesh;
    //std::shared_ptr<TickTimer> m_tickTimer;
    std::string m_enemyType;
    // 0-idle, 1-move, 2-attack, 3-death
    glm::vec4 m_indices;

    int m_pathStep;
    glm::vec3 m_moveDirection;
    float m_desiredRotation;
    float m_lastRotation;

    glm::vec3 m_pathStart;
    glm::vec3 m_pathDest;
    QList<glm::vec3> m_pathToTarget;
};

#endif // ENEMYAIRESPONSECOMPONENT_H
