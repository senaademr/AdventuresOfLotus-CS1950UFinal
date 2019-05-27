#ifndef ENEMYABILITYCOMPONENT_H
#define ENEMYABILITYCOMPONENT_H

#include "engine/components/component.h"

class EnemyAbilityComponent : public Component
{
public:
    EnemyAbilityComponent(float maxHealth, float movementSpeed, float damage, float experience);

    float getMaxHealth();
    float getCurrentHealth();
    float getMovementSpeed();
    float getDamage();
    float getExperience();
    bool getIsCounted();

    void dealDamage(float damage);
    bool isDead();
    void setIsCounted();


private:
    float m_maxHealth;
    float m_currentHealth;
    float m_movementSpeed;
    float m_damage;
    float m_experience;
    bool m_isCounted;
};

#endif // ENEMYABILITYCOMPONENT_H
