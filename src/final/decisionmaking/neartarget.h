#ifndef NEARTARGET_H
#define NEARTARGET_H
#include "engine/decisionmaking/condition.h"
#include <memory>
class EnemyAIResponseComponent;
class NearTarget : public Condition
{
public:
    NearTarget(std::map<std::string, std::string> &blackboard, std::shared_ptr<EnemyAIResponseComponent> &enemyResponse);
    ~NearTarget() override;
    Status update(float seconds) override;
    void reset() override;
private:
    std::shared_ptr<EnemyAIResponseComponent> m_enemyResponse;
};

#endif // NEARTARGET_H
