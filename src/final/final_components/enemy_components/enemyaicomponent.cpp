#include "enemyaicomponent.h"
#include "engine/decisionmaking/selector.h"
#include "engine/decisionmaking/sequence.h"
#include "engine/decisionmaking/composite.h"

#include "final/decisionmaking/findpathtotarget.h"
#include "final/decisionmaking/movetowardstarget.h"
#include "final/decisionmaking/neartarget.h"
#include "final/decisionmaking/setupdefense.h"
#include "final/decisionmaking/deadself.h"

#include "engine/basics/gameobject.h"

#include "enemyairesponsecomponent.h"
EnemyAIComponent::EnemyAIComponent(std::shared_ptr<EnemyAIResponseComponent> enemyAIResponseComponent) :
    AIComponent()
{
    std::shared_ptr<FindPathToTarget> pathToTarget = std::make_shared<FindPathToTarget>(m_blackboard, enemyAIResponseComponent);
    std::shared_ptr<MoveTowardsTarget> moveToTarget = std::make_shared<MoveTowardsTarget>(m_blackboard, enemyAIResponseComponent);
    std::shared_ptr<NearTarget> nearTarget = std::make_shared<NearTarget>(m_blackboard, enemyAIResponseComponent);
    std::shared_ptr<SetupDefense> setupDefense = std::make_shared<SetupDefense>(m_blackboard, enemyAIResponseComponent);
    std::shared_ptr<DeadSelf> deadSelf = std::make_shared<DeadSelf>(m_blackboard, enemyAIResponseComponent);

    //std::shared_ptr<Sequence> deadSelfSequence = std::make_shared<Sequence>(m_blackboard);
    //deadSelfSequence->addChild(deadSelf);

    std::shared_ptr<Sequence> defenseSequence = std::make_shared<Sequence>(m_blackboard);
    defenseSequence->addChild(nearTarget);
    defenseSequence->addChild(setupDefense);

    std::shared_ptr<Sequence> offenseSequence = std::make_shared<Sequence>(m_blackboard);
    offenseSequence->addChild(pathToTarget);
    offenseSequence->addChild(moveToTarget);

    m_rootSelector->addChild(deadSelf);
    m_rootSelector->addChild(defenseSequence);
    m_rootSelector->addChild(offenseSequence);
}

EnemyAIComponent::~EnemyAIComponent()
{

}
