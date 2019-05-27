#ifndef ENEMYAICOMPONENT_H
#define ENEMYAICOMPONENT_H
#include "engine/components/aicomponent.h"

class EnemyAIResponseComponent;
class EnemyAIComponent : public AIComponent
{
public:
    EnemyAIComponent(std::shared_ptr<EnemyAIResponseComponent>);
    ~EnemyAIComponent() override;
};

#endif // ENEMYAICOMPONENT_H
