#include "ticktimer.h"

#include "engine/util/CommonIncludes.h"

TickTimer::TickTimer(float secondsUntilTrue, bool allowOverflow)
    : m_secondsUntilTrue(secondsUntilTrue),
      m_allowOverflow(allowOverflow),
      m_currentTime(0)
{
}

void TickTimer::tick(float secondsPassed){
    m_currentTime += secondsPassed;

}

bool TickTimer::isTime(float secondsPassed){
    tick(secondsPassed);
    return isTime();

}

bool TickTimer::isTime(){
    if(m_currentTime >= m_secondsUntilTrue){
        if(m_allowOverflow){
            m_currentTime -= m_secondsUntilTrue;
        }
        else{
            m_currentTime = 0;
        }
        return true;
    }
    return false;
}


void TickTimer::setSecondsUntilTrue(float secondsUntilTrue){
    m_secondsUntilTrue = secondsUntilTrue;
}

void TickTimer::reset(){
    m_currentTime = 0;
}
