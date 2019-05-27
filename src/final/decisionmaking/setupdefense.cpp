#include "setupdefense.h"
#include "final/final_components/enemy_components/enemyairesponsecomponent.h"
#include <iostream>
SetupDefense::SetupDefense(std::map<std::string, std::string> &blackboard,
                               std::shared_ptr<EnemyAIResponseComponent> &enemyResponse)
     : Action(blackboard),
       m_enemyResponse(enemyResponse),
       m_durationInSeconds(1.5)
{

}

SetupDefense::~SetupDefense()
{

}

Status SetupDefense::update(float seconds)
{
    // attack target
    // std::cout << "defend" << std::endl;
    m_enemyResponse->attackTarget(seconds);
    m_durationInSeconds -= seconds;
    if (m_durationInSeconds <= 0) {
        return SUCCESS;
    }
    return RUNNING;
}

void SetupDefense::reset()
{
//    std::cout << "defend reset" << std::endl;
    m_enemyResponse->postAttackTarget();
    m_durationInSeconds = 1.5;
}
