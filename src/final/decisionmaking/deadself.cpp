#include "deadself.h"
#include "final/final_components/enemy_components/enemyairesponsecomponent.h"

DeadSelf::DeadSelf(std::map<std::string, std::string> &blackboard,
                   std::shared_ptr<EnemyAIResponseComponent> &enemyResponse)
    : Condition(blackboard), m_enemyResponse(enemyResponse)
{

}

DeadSelf::~DeadSelf()
{

}

Status DeadSelf::update(float seconds)
{
    if (m_enemyResponse->isDead())
    {
        return SUCCESS;
    }
    return FAIL;
}

void DeadSelf::reset()
{
    // nothing to reset
}
