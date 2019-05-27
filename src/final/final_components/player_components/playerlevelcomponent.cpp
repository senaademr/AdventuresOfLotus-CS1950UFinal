#include "playerlevelcomponent.h"

#include "engine/basics/gameobject.h"
#include "playerabilitycomponent.h"
#include "engine/components/uicomponent.h"
#include "engine/UI/uipanel.h"


PlayerLevelComponent::PlayerLevelComponent()
    : m_experience(0),
      m_currentLevel(0)
{
}

void PlayerLevelComponent::addExperience(float newExperience){
    m_experience += newExperience;


    while(m_experience >= getTotalExperienceNeededForNextLevel()){
        float experienceNeeded = getTotalExperienceNeededForNextLevel();
        m_experience -= experienceNeeded;
        m_currentLevel ++;
    }
    getGameObject()->getComponent<UIComponent>()->getPanel("levelPanel")->callbackAll();
    updateAttributes();

}

float PlayerLevelComponent::getTotalExperienceNeededForNextLevel(){
    return 100.f * (m_currentLevel+1);
}

float PlayerLevelComponent::getProgressTowardNextLevelExperience(){
    return m_experience;
}

void PlayerLevelComponent::updateAttributes(){
    float maxHealth = START_HEALTH + m_currentLevel * 10.f;
    float maxStamina = START_STAMINA + m_currentLevel * 5.f;
    float damage = START_DAMAGE + m_currentLevel * 1.f;
    float movementSpeed = START_MOVEMENT_SPEED + m_currentLevel * .3f;
    int numCircles = getNumCirclesByLevel();
    float baseAttackSpeed = START_ATTACK_SPEED * std::pow(.93f, m_currentLevel);

    float healthRegenRate = START_HEALTH_GAIN_RATE + 1.f * m_currentLevel;
    float staminaRegenRate = START_STAMINA_GAIN_RATE + .5f * m_currentLevel;
    float passiveStaminaRegenRate = START_STAMINA_PASSIVE_REGEN_RATE  + .2f* m_currentLevel;
    float impactPower = START_IMPACT_POWER + 3.f * m_currentLevel;


    std::shared_ptr<PlayerAbilityComponent> playerAbility = m_gameObject->getComponent<PlayerAbilityComponent>();
    playerAbility->setMaxHealth(maxHealth);
    playerAbility->setBaseDamage(damage);
    playerAbility->setMovementSpeed(movementSpeed);
    playerAbility->setMaxStamina(maxStamina);
    playerAbility->setNumberAttacks(numCircles);
    playerAbility->setBaseAttackSpeed(baseAttackSpeed);

    playerAbility->setMeditationHealthRegenRate(healthRegenRate);
    playerAbility->setMeditationRegenRate(staminaRegenRate);
    playerAbility->setPassiveStaminaRegenRate(passiveStaminaRegenRate);
    playerAbility->setImpactPower(impactPower);
}

int PlayerLevelComponent::getNumCirclesByLevel(){
    int numCircles = 0;
    if(m_currentLevel < 3){
        numCircles = 2;
    }
    else if(m_currentLevel < 6){
        numCircles = 3;
    }
    else if(m_currentLevel < 9){
        numCircles = 4;
    }
    else if(m_currentLevel < 12){
        numCircles = 5;
    }
    else{
        numCircles = 6;
    }

    return numCircles;
}

//void PlayerLevelComponent::experienceThreshholds(){
////    experienceThreshholds = [100, 300, 700, 1300, 2100]
//}

float PlayerLevelComponent::getExperience(){
    return m_experience;
}

int PlayerLevelComponent::getCurrentLevel(){
    return m_currentLevel;
}
