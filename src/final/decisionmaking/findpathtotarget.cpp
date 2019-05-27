#include "findpathtotarget.h"
#include "final/final_components/enemy_components/enemyairesponsecomponent.h"
#include <iostream>
FindPathToTarget::FindPathToTarget(std::map<std::string, std::string> &blackboard,
                                   std::shared_ptr<EnemyAIResponseComponent> &enemyResponse)
    : Action(blackboard),
      m_enemyResponse(enemyResponse)
{

}

FindPathToTarget::~FindPathToTarget()
{

}

Status FindPathToTarget::update(float seconds)
{
    // call pathfinding
    //std::cout << "find path" << std::endl;
    if (m_enemyResponse->updatePathTarget()) {
        return SUCCESS;
    }
    return FAIL;
}

void FindPathToTarget::reset()
{

}
