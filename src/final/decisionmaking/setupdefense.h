#ifndef SETUPDEFENSE_H
#define SETUPDEFENSE_H
#include "engine/decisionmaking/action.h"
#include <memory>
class EnemyAIResponseComponent;
class SetupDefense : public Action
{
public:
    SetupDefense(std::map<std::string, std::string> &blackboard, std::shared_ptr<EnemyAIResponseComponent> &enemyResponse);
    ~SetupDefense() override;
    Status update(float seconds) override;
    void reset() override;
private:
    std::shared_ptr<EnemyAIResponseComponent> m_enemyResponse;
    float m_durationInSeconds;
};

#endif // SETUPDEFENSE_H
