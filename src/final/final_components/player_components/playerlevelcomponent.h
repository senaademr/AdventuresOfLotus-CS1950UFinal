#ifndef PLAYERLEVELCOMPONENT_H
#define PLAYERLEVELCOMPONENT_H

#include "engine/components/component.h"
#include <QList>

class PlayerLevelComponent : public Component
{
public:
    PlayerLevelComponent();

    void addExperience(float newExperience);
    float getExperience();

    float getTotalExperienceNeededForNextLevel();
    float getProgressTowardNextLevelExperience();

    void updateAttributes();
    int getNumCirclesByLevel();

    int getCurrentLevel();

    static constexpr float START_HEALTH = 50.f;
    static constexpr float START_STAMINA = 50.f;
    static constexpr float START_DAMAGE = 5.f;
    static constexpr float START_MOVEMENT_SPEED = 7.f;
    static constexpr float START_ATTACK_SPEED = .5f;
    static const int START_NUM_ATTACKS = 2;
    static constexpr float START_HEALTH_GAIN_RATE = 5.f;
    static constexpr float START_STAMINA_GAIN_RATE  = 10.f;
    static constexpr float START_STAMINA_PASSIVE_REGEN_RATE = 2.f;
    static constexpr float START_IMPACT_POWER = 20.f;

private:
    float m_experience;
    int m_currentLevel;
    QList<int> m_totalExperienceToLevel;
};

#endif // PLAYERLEVELCOMPONENT_H
