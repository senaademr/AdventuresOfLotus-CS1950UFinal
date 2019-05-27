#include "playerabilitycomponent.h"
#include "engine/components/animationcomponent.h"
#include "engine/basics/gameobject.h"
#include "engine/components/uicomponent.h"
#include "engine/UI/uipanel.h"
#include "final/final_components/player_components/playerlevelcomponent.h"

PlayerAbilityComponent::PlayerAbilityComponent() : Component(), Tickable(),
  m_maxHealth(PlayerLevelComponent::START_HEALTH),
  m_currentHealth(PlayerLevelComponent::START_HEALTH),
  m_maxStamina(PlayerLevelComponent::START_STAMINA),
  m_currentStamina(PlayerLevelComponent::START_STAMINA),
  m_movementSpeed(PlayerLevelComponent::START_MOVEMENT_SPEED),
  m_baseAttackSpeed(PlayerLevelComponent::START_ATTACK_SPEED),
  m_currentAttack(0),
  m_numAttacks(PlayerLevelComponent::START_NUM_ATTACKS),
  m_baseDamage(PlayerLevelComponent::START_DAMAGE),
  m_meditationHealthRegenRate(PlayerLevelComponent::START_HEALTH_GAIN_RATE),
  m_meditationStaminaRegenRate(PlayerLevelComponent::START_STAMINA_GAIN_RATE),
  m_passiveStaminaRegenRate(PlayerLevelComponent::START_STAMINA_PASSIVE_REGEN_RATE),
  m_impactPower(PlayerLevelComponent::START_IMPACT_POWER)
{
}

void PlayerAbilityComponent::tick(float seconds){
    if(m_currentHealth <= 0){
        m_dead = true;
        std::shared_ptr<GameObject> gameObject = this->getGameObject();
        gameObject->getComponent<AnimationComponent>()->changeCurrentAnimation("death");
    }
}

void PlayerAbilityComponent::updateAttackAnimations(){
    std::shared_ptr<AnimationComponent> playerAnim = m_gameObject->getComponent<AnimationComponent>();

    float leftPunchFrames = 10.f;
    float leftPunchTime = AnimationComponent::getAttackFrameSpeed(getAttackSpeed("leftpunch"), leftPunchFrames);

    float rightPunchFrames = 10.f;
    float rightPunchTime = AnimationComponent::getAttackFrameSpeed(getAttackSpeed("rightpunch"), leftPunchFrames);

    float stompFrames = 17.f;
    float stompTime = AnimationComponent::getAttackFrameSpeed(getAttackSpeed("stomp"), stompFrames);

    playerAnim->add("leftpunch", leftPunchTime, leftPunchFrames, 690.f, 0.f);
    playerAnim->add("rightpunch", rightPunchTime, rightPunchFrames, 670.f, 0.f);
    playerAnim->add("stomp", stompTime, stompFrames, 900.f, 0.f);
}


float PlayerAbilityComponent::getMaxHealth(){
    return m_maxHealth;
}

float PlayerAbilityComponent::getCurrentHealth(){
    return m_currentHealth;
}

void PlayerAbilityComponent::addToCurrentHealth(float health){
    m_currentHealth += health;
    if(m_currentHealth < 0){
        m_currentHealth = 0;
        m_dead = true;
    }
    if(m_currentHealth > m_maxHealth){
        m_currentHealth = m_maxHealth;
    }
    getGameObject()->getComponent<UIComponent>()->getPanel("barPanel")->callbackAll();
}

void PlayerAbilityComponent::setMaxHealth(float newMax){
    float healthIncrease = newMax - m_maxHealth;
    m_maxHealth = newMax;
    if(healthIncrease > 0){
        addToCurrentHealth(healthIncrease);
    }
}

float PlayerAbilityComponent::getMaxStamina(){
    return m_maxStamina;
}

float PlayerAbilityComponent::getCurrentStamina(){
    return m_currentStamina;
}

void PlayerAbilityComponent::addToCurrentStamina(float stamina){
    m_currentStamina += stamina;
    if(m_currentStamina < 0){
        m_currentStamina = 0;
    }
    if(m_currentStamina > m_maxStamina){
        m_currentStamina = m_maxStamina;
    }
    getGameObject()->getComponent<UIComponent>()->getPanel("barPanel")->callbackAll();
}

void PlayerAbilityComponent::setMaxStamina(float newMax){
    float staminaIncrease = newMax - m_maxStamina;
    m_maxStamina = newMax;
    if(staminaIncrease > 0){
        addToCurrentStamina(staminaIncrease);
    }
}


float PlayerAbilityComponent::getMovementSpeed(){
    return m_movementSpeed;
}

void PlayerAbilityComponent::setMovementSpeed(float movementSpeed){
    m_movementSpeed= movementSpeed;
}

float PlayerAbilityComponent::getAttackSpeed(std::string attackName){
    if(attackName.compare("leftpunch") == 0){
        return m_baseAttackSpeed;
    }
    if(attackName.compare("rightpunch") == 0){
        return m_baseAttackSpeed*2.f;

    }
    if(attackName.compare("stomp") == 0){
        return m_baseAttackSpeed* 3.f;
    }
    std::cout << "no attacknamed: " << attackName << std::endl;
    return 1.f;
}


void PlayerAbilityComponent::setBaseAttackSpeed(float newBaseAttackSpeed){
    m_baseAttackSpeed = newBaseAttackSpeed;
    updateAttackAnimations();
}

void PlayerAbilityComponent::addAttack(std::string attackName){
    m_attacks.push_back(attackName);
}

void PlayerAbilityComponent::switchAttack(bool direction){
    if(direction){
        if(m_currentAttack+1 != m_attacks.size()){
            m_currentAttack++;
        } else {
            m_currentAttack = 0;
        }
    } else {
        if(m_currentAttack != 0){
            m_currentAttack--;
        } else {
            m_currentAttack = m_attacks.size()-1;
        }
    }  
}

std::string PlayerAbilityComponent::getCurrentAttack(){
    return m_attacks[m_currentAttack];
}

bool PlayerAbilityComponent::isDead(){
    return m_dead;
}


int PlayerAbilityComponent::getNumberAttacks(){
    return m_numAttacks;
}

void PlayerAbilityComponent::setNumberAttacks(int newNumberAttacks){
    m_numAttacks = newNumberAttacks;
}

void PlayerAbilityComponent::incrementNumberAttacks(){
    m_numAttacks ++;
}


float PlayerAbilityComponent::getBaseDamage(){
    return m_baseDamage;
}


void PlayerAbilityComponent::setBaseDamage(float newDamage){
    m_baseDamage = newDamage;
}


float PlayerAbilityComponent::getMeditationHealthRegenRate(){
    return m_meditationHealthRegenRate;
}

float PlayerAbilityComponent::getMediationStaminaRegenRate(){
    return m_meditationStaminaRegenRate;
}


float PlayerAbilityComponent::getPassiveStaminaRegenRate(){
    return m_passiveStaminaRegenRate;
}

void PlayerAbilityComponent::setMeditationHealthRegenRate(float healthRegenRate){
    m_meditationHealthRegenRate = healthRegenRate;
}

void PlayerAbilityComponent::setMeditationRegenRate(float staminaRegenRate){
    m_meditationStaminaRegenRate = staminaRegenRate;
}

void PlayerAbilityComponent::setPassiveStaminaRegenRate(float passiveStaminaRegenRate){
    m_passiveStaminaRegenRate = passiveStaminaRegenRate;
}


float PlayerAbilityComponent::getImpactPower(){
    return m_impactPower;
}

void PlayerAbilityComponent::setImpactPower(float newImpact){
    m_impactPower = newImpact;
}
