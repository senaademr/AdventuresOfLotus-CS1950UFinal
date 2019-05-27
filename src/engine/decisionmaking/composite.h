#ifndef COMPOSITE_H
#define COMPOSITE_H
#include "btnode.h"
#include <memory>
#include <vector>

class Composite : public BTNode
{
public:
    Composite(std::map<std::string, std::string> &blackboard);
    virtual ~Composite() override;
    virtual Status update(float seconds) = 0;
    virtual void reset() = 0;
    void addChild(const std::shared_ptr<BTNode> &child);

protected:
    std::vector<std::shared_ptr<BTNode>> m_children;
    int m_lastRunning;
};

#endif // COMPOSITE_H
