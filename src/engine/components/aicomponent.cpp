#include "aicomponent.h"
#include "engine/decisionmaking/selector.h"
#include "engine/decisionmaking/composite.h"

#include <iostream>
AIComponent::AIComponent() :
    Component(), Tickable(),
    m_blackboard(),
    m_rootSelector(std::make_shared<Selector>(m_blackboard))
{

}

AIComponent::~AIComponent()
{

}

void AIComponent::tick(float seconds)
{
//    std::cout << "AI tick" << std::endl;
    Status status = m_rootSelector->update(seconds);
    if (status != RUNNING) { // reset if not running
        m_rootSelector->reset();
    }
}
