#ifndef PLAYERABILITYCOMPONENT_H
#define PLAYERABILITYCOMPONENT_H

#include "engine/components/component.h"
#include "engine/components/tickable.h"
#include "final/abilities/abilityconstants.h"

#include <vector>


class PlayerAbilityComponent : public Component, public Tickable
{
public:
    PlayerAbilityComponent();

    void tick(float seconds) override;
    void updateAttackAnimations();

    float getMaxHealth();
    float getCurrentHealth();
    void addToCurrentHealth(float health);
    void setMaxHealth(float newMax);

    float getMaxStamina();
    float getCurrentStamina();
    void addToCurrentStamina(float stamina);
    void setMaxStamina(float newMax);

    float getMovementSpeed();
    void setMovementSpeed(float movementSpeed);

    float getAttackSpeed(std::string attackName);
    void setBaseAttackSpeed(float newBaseAttackSpeed);

    void addAttack(std::string attackName);
    // false moves left, true moves right
    void switchAttack(bool direction);
    std::string getCurrentAttack();

    bool isDead();

    int getNumberAttacks();
    void setNumberAttacks(int newNumberAttacks);
    void incrementNumberAttacks();

    float getBaseDamage();
    void setBaseDamage(float newDamage);

    float getMeditationHealthRegenRate();
    float getMediationStaminaRegenRate();
    float getPassiveStaminaRegenRate();

    void setMeditationHealthRegenRate(float healthRegenRate);
    void setMeditationRegenRate(float staminaRegenRate);
    void setPassiveStaminaRegenRate(float passiveStaminaRegenRate);

    float getImpactPower();
    void setImpactPower(float newImpact);

private:
    float m_maxHealth;
    float m_currentHealth ;
    float m_maxStamina;
    float m_currentStamina;
    float m_movementSpeed;
    float m_baseAttackSpeed;
    int m_currentAttack;
    int m_numAttacks;
    float m_baseDamage;
    float m_meditationHealthRegenRate;
    float m_meditationStaminaRegenRate;
    float m_passiveStaminaRegenRate;
    float m_impactPower;
    std::vector<std::string> m_attacks;
    bool m_dead = false;
};

#endif // PLAYERABILITYCOMPONENT_H
