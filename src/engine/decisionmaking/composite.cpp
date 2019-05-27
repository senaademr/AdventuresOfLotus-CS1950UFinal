#include "composite.h"

Composite::Composite(std::map<std::string, std::string> &blackboard) : BTNode(blackboard),
    m_lastRunning(-1)
{

}

Composite::~Composite()
{

}

Status Composite::update(float seconds)
{

}

void Composite::reset()
{

}

void Composite::addChild(const std::shared_ptr<BTNode> &child)
{
    m_children.push_back(child);
}

