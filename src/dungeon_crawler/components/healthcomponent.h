#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "engine/components/tickable.h"
#include "engine/components/component.h"

class GameWorld;

class HealthComponent : public Component, public Tickable
{
public:
    HealthComponent(int health);

    // Tickable interface
public:
    void tick(float seconds);
    int getHealth();
    void dealDamage(int damage);

    bool isDead();

private:
    int m_health;
};

#endif // HEALTHCOMPONENT_H
