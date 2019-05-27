#include "neartarget.h"
#include "final/final_components/enemy_components/enemyairesponsecomponent.h"
#include <iostream>
NearTarget::NearTarget(std::map<std::string, std::string> &blackboard,
                       std::shared_ptr<EnemyAIResponseComponent> &enemyResponse)
  : Condition(blackboard),
    m_enemyResponse(enemyResponse)
{

}

NearTarget::~NearTarget()
{

}

Status NearTarget::update(float seconds)
{
    //std::cout << "near target?" << std::endl;
    if (m_enemyResponse->nearTarget())
    {
       // std::cout << "Yes" << std::endl;
        return SUCCESS;
    }
    //std::cout << "No" << std::endl;
    return FAIL;
}

void NearTarget::reset()
{
    // nothing to reset
}
