#include "movetowardstarget.h"

#include "final/final_components/enemy_components/enemyairesponsecomponent.h"
#include <iostream>
MoveTowardsTarget::MoveTowardsTarget(std::map<std::string, std::string> &blackboard,
                                     std::shared_ptr<EnemyAIResponseComponent> &enemyResponse)
     : Action(blackboard),
       m_enemyResponse(enemyResponse)
{

}

MoveTowardsTarget::~MoveTowardsTarget()
{

}

Status MoveTowardsTarget::update(float seconds)
{
    // move towards target according to path
//    std::cout << "make next move" << std::endl;
    m_enemyResponse->makeNextMove(seconds);
    return SUCCESS;
}

void MoveTowardsTarget::reset()
{

}
