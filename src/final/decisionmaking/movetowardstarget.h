#ifndef MOVETOWARDSTARGET_H
#define MOVETOWARDSTARGET_H
#include "engine/decisionmaking/action.h"
#include <memory>
class EnemyAIResponseComponent;
class MoveTowardsTarget : public Action
{
public:
    MoveTowardsTarget(std::map<std::string, std::string> &blackboard, std::shared_ptr<EnemyAIResponseComponent> &enemyResponse);
    ~MoveTowardsTarget() override;
    Status update(float seconds) override;
    void reset() override;
private:
    std::shared_ptr<EnemyAIResponseComponent> m_enemyResponse;
};

#endif // MOVETOWARDSTARGET_H
