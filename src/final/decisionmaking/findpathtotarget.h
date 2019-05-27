#ifndef FINDPATHTOTARGET_H
#define FINDPATHTOTARGET_H
#include "engine/decisionmaking/action.h"
#include <memory>
class EnemyAIResponseComponent;
class FindPathToTarget : public Action
{
public:
    FindPathToTarget(std::map<std::string, std::string> &blackboard, std::shared_ptr<EnemyAIResponseComponent> &enemyResponse);
    ~FindPathToTarget() override;
    Status update(float seconds) override;
    void reset() override;
private:
    std::shared_ptr<EnemyAIResponseComponent> m_enemyResponse;
};

#endif // FINDPATHTOTARGET_H
