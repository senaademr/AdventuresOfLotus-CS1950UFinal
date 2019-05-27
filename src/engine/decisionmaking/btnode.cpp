#include "btnode.h"
#include <string>

BTNode::BTNode(std::map<std::string, std::string> &blackboard) :
    m_blackboard(blackboard)
{

}
BTNode::~BTNode()
{

}

void BTNode::writeToBlackboard(const std::string &key, const std::string &value)
{
    m_blackboard[key] = value;
}

std::string BTNode::readFromBlackbload(const std::string &key) const
{
    return m_blackboard[key];
}

