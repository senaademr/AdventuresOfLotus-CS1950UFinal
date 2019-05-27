#include "timeremovecomponent.h"

#include "engine/util/ticktimer.h"
#include "engine/basics/gameworld.h"


TimeRemoveComponent::TimeRemoveComponent(std::shared_ptr<GameWorld> gameWorld, float timeTillRemove)
    : Component(),
      m_gameWorld(gameWorld),
      m_tickTimer(nullptr)
{
    m_tickTimer = std::make_shared<TickTimer>(timeTillRemove, false);
}


void TimeRemoveComponent::tick(float seconds){
    if(m_isTimerOn){
        if(m_tickTimer->isTime(seconds)){
            remove();
        }
    }
}

void TimeRemoveComponent::remove(){
//    std::cout << "removing component after time" << std::endl;
    m_gameWorld->removeObject(getGameObject());
}


void TimeRemoveComponent::setisTimerOn(bool isTimerOn){
    m_isTimerOn = isTimerOn;
}
