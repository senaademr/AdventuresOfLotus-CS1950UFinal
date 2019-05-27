#include "healthcomponent.h"

HealthComponent::HealthComponent(int health)
    : Component(),
      m_health(health)
{
}

void HealthComponent::tick(float seconds){

}

int HealthComponent::getHealth(){
    return m_health;
}
void HealthComponent::dealDamage(int damage){
    m_health -= damage;
}

bool HealthComponent::isDead(){
    return m_health <= 0;
}
