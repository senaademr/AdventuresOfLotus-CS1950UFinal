#include "enemyabilitycomponent.h"

#include "engine/basics/gameobject.h"
#include "engine/components/uicomponent.h"
#include "engine/UI/uipanel.h"

EnemyAbilityComponent::EnemyAbilityComponent(float maxHealth, float movementSpeed, float damage, float experience)
    : Component(),
      m_maxHealth(maxHealth),
      m_currentHealth(maxHealth),
      m_movementSpeed(movementSpeed),
      m_damage(damage),
      m_experience(experience),
      m_isCounted(false)
{
}


float EnemyAbilityComponent::getMaxHealth(){
    return m_maxHealth;
}

float EnemyAbilityComponent::getCurrentHealth(){
    return m_currentHealth;
}

float EnemyAbilityComponent::getMovementSpeed(){
    return m_movementSpeed;
}

float EnemyAbilityComponent::getDamage(){
    return m_damage;
}


float EnemyAbilityComponent::getExperience(){
    return m_experience;
}


bool EnemyAbilityComponent::getIsCounted(){
    return m_isCounted;
}


void EnemyAbilityComponent::dealDamage(float damage){
    m_currentHealth -= damage;
    getGameObject()->getComponent<UIComponent>()->getPanel("enemyPanel")->callbackAll();
}


bool EnemyAbilityComponent::isDead(){
    return m_currentHealth <= 0;
}


void EnemyAbilityComponent::setIsCounted(){
    m_isCounted = true;
}
