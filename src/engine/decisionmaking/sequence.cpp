#include "sequence.h"

Sequence::Sequence(std::map<std::string, std::string> &blackboard) : Composite(blackboard)
{

}

Sequence::~Sequence()
{

}

Status Sequence::update(float seconds)
{
    if (m_lastRunning <= -1 || m_lastRunning >= m_children.size()) { // out of bound
        m_lastRunning = 0;
    }
    std::shared_ptr<BTNode> running =  m_children.at(m_lastRunning);
    assert(running);
    Status status = running->update(seconds);

    Status result = RUNNING;
    if (status == FAIL) { // If one behavior fails then the whole sequence fails, hence “sequence”
        result = FAIL;
    } else if (status == SUCCESS) {
        ++m_lastRunning; // Advance to next child only if last running SUCCEED
        if (m_lastRunning == m_children.size()) {
            for (std::shared_ptr<BTNode> const &child : m_children) { // Reset all children
                child->reset();
            }
            m_lastRunning = -1; // Reset
            result = SUCCESS; // Returns SUCCESS if the entire sequence completes
        }
    }

    return result;
}

void Sequence::reset()
{
    if (m_lastRunning <= -1 || m_lastRunning >= m_children.size()) { // out of bound
        return;
    }
    m_children.at(m_lastRunning)->reset(); // Reset lastRunning child but NOT changing lastRunning child
}
