#ifndef DEADSELF_H
#define DEADSELF_H

#include "engine/decisionmaking/condition.h"
#include <memory>

class EnemyAIResponseComponent;
class DeadSelf : public Condition
{
public:
    DeadSelf(std::map<std::string, std::string> &blackboard,
             std::shared_ptr<EnemyAIResponseComponent> &enemyResponse);
    ~DeadSelf() override;
    Status update(float seconds) override;
    void reset() override;
private:
    std::shared_ptr<EnemyAIResponseComponent> m_enemyResponse;
};

#endif // DEADSELF_H
