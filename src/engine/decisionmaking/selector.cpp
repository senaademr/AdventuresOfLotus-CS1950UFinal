#include "selector.h"
#include <iostream>

Selector::Selector(std::map<std::string, std::string> &blackboard) : Composite(blackboard)
{

}

Selector::~Selector()
{

}

Status Selector::update(float seconds)
{
    if (m_lastRunning <= -1 || m_lastRunning >= m_children.size()) { // out of bound
        m_lastRunning = 0;
    }
    //std::cout << std::to_string(m_children.size()) << std::endl;
    assert(m_lastRunning >= 0);
    assert(m_lastRunning < m_children.size());

    std::shared_ptr<BTNode> running =  m_children.at(m_lastRunning);
    assert(running);
    Status status = running->update(seconds);

    Status result = RUNNING;
    if (status == SUCCESS) {
        result = SUCCESS; // Return SUCCESS if any child succeeds
    } else if (status == FAIL) {
        ++m_lastRunning;
        if (m_lastRunning == m_children.size()) {
            result = FAIL; // Return FAIL only if all children fail
        }
    }

    return result;
}

void Selector::reset()
{
    // Should reset the previously running child if a child before it starts RUNNING
    for (std::shared_ptr<BTNode> const &child : m_children) {
        child->reset();
    }
    m_lastRunning = -1;
}
