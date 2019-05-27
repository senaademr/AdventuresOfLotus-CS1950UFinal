#include "enemyairesponsecomponent.h"

#include "engine/components/transformcomponent.h"
#include "engine/components/physicscomponent.h"
#include "engine/components/animationcomponent.h"
#include "engine/navigation/navigationmesh.h"
#include "engine/basics/gameworld.h"
#include "engine/basics/gameobject.h"
#include "final/final_components/player_components/dynamicmovecomponent.h"
#include "final/final_components/enemy_components/enemyabilitycomponent.h"

EnemyAIResponseComponent::EnemyAIResponseComponent(
        std::shared_ptr<TransformComponent> targetTransform,
        std::shared_ptr<NavigationMesh> navmesh,
        std::string enemyType) :
    AIResponseComponent(),

    m_targetTransform(targetTransform),
    m_navmesh(navmesh),
    m_enemyType(enemyType),

    m_pathStep(1),
    m_moveDirection(glm::vec3(0.f)),
    m_desiredRotation(0.f),
    m_lastRotation(0.f),

    m_pathStart(glm::vec3(0.f)),
    m_pathDest(glm::vec3(0.f)),
    m_pathToTarget(QList<glm::vec3>())
{

    assert(m_targetTransform);
    loadAnimationIndices();
}

EnemyAIResponseComponent::~EnemyAIResponseComponent()
{

}

bool EnemyAIResponseComponent::updatePathTarget()
{
    glm::vec3 targetPos = m_targetTransform->getPosition();

    if (m_pathToTarget.size() > m_pathStep+1 && m_pathDest == targetPos) {
//        std::cout << "no path change" << std::endl;
        return true;
    }

    glm::vec3 startPos = m_gameObject->getComponent<TransformComponent>()->getPosition();
    m_pathToTarget = m_navmesh->navigate(startPos, targetPos);

    if(m_pathToTarget.size() < 2){
//        std::cout << "cannot find path to player" << std::endl;
        return false;
    }

//    std::cout << "path refreshed" << std::endl;
    m_pathStart = startPos;
    m_pathDest = targetPos;
    m_pathStep = 1;
    m_moveDirection = glm::normalize((m_pathToTarget.at(m_pathStep)-startPos) * glm::vec3(1, 0, 1));
    setDesiredRotation(m_moveDirection);

    return true;
}

void EnemyAIResponseComponent::setDesiredRotation(const glm::vec3 &direction) {
    float cosAngle = glm::dot(direction, glm::vec3(0.f, 0.f, 1.f));
    float angle = glm::acos(cosAngle);
    if(m_moveDirection.x > 0){
        m_desiredRotation = glm::radians(180.f) + angle;
    }
    else{
        m_desiredRotation = glm::radians(180.f) - angle;
    }
}

void EnemyAIResponseComponent::makeNextMove(float seconds)
{

//    if (m_lastRotation != m_desiredRotation) {
//        if (glm::abs(m_lastRotation - m_desiredRotation) < 0.5f) {
//            m_gameObject->getComponent<TransformComponent>()->setRotation(m_desiredRotation, glm::vec3(0, 1, 0));
//            m_lastRotation = m_desiredRotation;
//        } else {
//            bool positiveDirection = true;
//            if (m_desiredRotation > m_lastRotation && m_desiredRotation - m_lastRotation > glm::radians(180.f)) {
//                positiveDirection = false;
//            }
//            float rotation;
//            if (positiveDirection) {
//                rotation = glm::mod((m_lastRotation + rotationSpeed * seconds), glm::radians(360.f));
//            } else {
//                rotation = glm::mod((m_lastRotation + glm::radians(360.f) - rotationSpeed * seconds), glm::radians(360.f));
//            }
//            m_gameObject->getComponent<TransformComponent>()->setRotation(rotation, glm::vec3(0, 1, 0));
//            m_lastRotation = rotation;
//        }
//    }

    if (m_lastRotation > m_desiredRotation) {
        float rotation = m_lastRotation - rotationSpeed * seconds;
        if (rotation < m_desiredRotation) {
            m_gameObject->getComponent<TransformComponent>()->setRotation(m_desiredRotation, glm::vec3(0, 1, 0));
            m_lastRotation = m_desiredRotation;
        } else {
            m_gameObject->getComponent<TransformComponent>()->setRotation(rotation, glm::vec3(0, 1, 0));
            m_lastRotation = rotation;
        }
    } else if (m_lastRotation < m_desiredRotation) {
        float rotation = m_lastRotation + rotationSpeed * seconds;
        if (rotation > m_desiredRotation) {
            m_gameObject->getComponent<TransformComponent>()->setRotation(m_desiredRotation, glm::vec3(0, 1, 0));
            m_lastRotation = m_desiredRotation;
        } else {
            m_gameObject->getComponent<TransformComponent>()->setRotation(rotation, glm::vec3(0, 1, 0));
            m_lastRotation = rotation;
        }
    } else {
//        std::cout << "no need to rotate" << std::endl;
    }

    if(m_moveDirection.x != 0 || m_moveDirection.z != 0){
        //std::cout << "walk animation" << std::endl;
        m_gameObject->getComponent<AnimationComponent>()->changeAnimation(m_indices.y);
        m_gameObject->getComponent<DynamicMoveComponent>()->setDesiredDirection(m_moveDirection);

    } else {
        //std::cout << "idle animation" << std::endl;
        m_gameObject->getComponent<AnimationComponent>()->changeAnimation(m_indices.x);
        m_gameObject->getComponent<DynamicMoveComponent>()->setDesiredDirection(glm::vec3(0));
    }

    glm::vec3 currentPos = m_gameObject->getComponent<TransformComponent>()->getPosition();

    glm::vec3 nextPos = m_pathToTarget.at(m_pathStep);
    if (glm::distance2(currentPos, nextPos) < 0.000001 && m_pathToTarget.size() > m_pathStep+1) { // very close to nextPos
        m_pathStep++;
        m_moveDirection = glm::normalize((m_pathToTarget.at(m_pathStep)-currentPos) * glm::vec3(1, 0, 1));
        setDesiredRotation(m_moveDirection);
    }

//    std::cout << "move" << std::endl;
}

void EnemyAIResponseComponent::attackTarget(float seconds)
{
    float velocity = m_gameObject->getComponent<EnemyAbilityComponent>()->getMovementSpeed();
    glm::vec3 direction = glm::normalize(m_targetTransform->getPosition() - m_gameObject->getComponent<TransformComponent>()->getPosition());
    if(direction.x != 0 || direction.z != 0){
        float cosAngle = glm::dot(direction, glm::vec3(0.f, 0.f, 1.f));
        float angle = glm::acos(cosAngle);
        if(direction.x > 0){
            m_desiredRotation = glm::radians(180.f) + angle;
        }
        else{
            m_desiredRotation = glm::radians(180.f) - angle;
        }
        m_gameObject->getComponent<PhysicsComponent>()->setXVelocity(direction.x * velocity);
        m_gameObject->getComponent<PhysicsComponent>()->setZVelocity(direction.z * velocity);
    }
    //std::cout << "attack animation" << std::endl;
    m_gameObject->getComponent<AnimationComponent>()->changeAnimation(m_indices.z);
    m_gameObject->getComponent<TransformComponent>()->setRotation(m_desiredRotation, glm::vec3(0, 1, 0));

}

void EnemyAIResponseComponent::postAttackTarget() const
{
    // back
}

bool EnemyAIResponseComponent::nearTarget() const
{
    float squaredDist = glm::distance2(m_gameObject->getComponent<TransformComponent>()->getPosition(), m_targetTransform->getPosition());
    float attackDistance = 4.f;

    if(squaredDist > attackDistance * attackDistance) {
        //m_gameObject->getComponent<AnimationComponent>()->changeAnimation(m_indices.x);
        //m_gameObject->getComponent<PhysicsComponent>()->setXVelocity(0);
        //m_gameObject->getComponent<PhysicsComponent>()->setZVelocity(0);
        return false;
    }

    return true;
}

bool EnemyAIResponseComponent::isDead() const
{
    bool isDead = m_gameObject->getComponent<EnemyAbilityComponent>()->isDead();
    if (isDead) {
//        std::cout << "die animation" << std::endl;
        m_gameObject->getComponent<AnimationComponent>()->changeAnimation(m_indices.w);
        std::shared_ptr<PhysicsComponent> physics = m_gameObject->getComponent<PhysicsComponent>();
        physics->setXVelocity(0);
        physics->setZVelocity(0);
    }
    return isDead;
}

void EnemyAIResponseComponent::loadAnimationIndices()
{
    glm::vec4 indices = glm::vec4(0);
    if(!m_enemyType.compare("spider")){
        indices.x = 14;
        indices.y = 11;
        indices.z = 2;
        indices.w = 1;
    }
    else if(!m_enemyType.compare("magma")){
        indices.x = 6;
        indices.y = 11;
        indices.z = 9;
        indices.w = 3;
    }
    else if(!m_enemyType.compare("space")){
        indices.x = 7;
        indices.y = 9;
        indices.z = 2;
        indices.w = 5;
    }
    m_indices = indices;
}
