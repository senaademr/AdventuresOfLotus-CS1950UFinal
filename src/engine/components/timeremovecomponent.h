#ifndef TIMEREMOVECOMPONENT_H
#define TIMEREMOVECOMPONENT_H

#include "component.h"
#include "tickable.h"

class TickTimer;
class GameWorld;

class TimeRemoveComponent : public Component, public Tickable
{
public:
    TimeRemoveComponent(std::shared_ptr<GameWorld> gameWorld, float timeTillRemove);

    // Tickable interface
public:
    void tick(float seconds);
    void setisTimerOn(bool isTimerOn);
    virtual void remove();

private:
    std::shared_ptr<GameWorld> m_gameWorld;
    std::shared_ptr<TickTimer> m_tickTimer;
    bool m_isTimerOn = true;
};

#endif // TIMEREMOVECOMPONENT_H
