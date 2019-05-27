#ifndef ACTION_H
#define ACTION_H
#include "btnode.h"

class Action : public BTNode
{
public:
    Action(std::map<std::string, std::string> &blackboard);
    ~Action() override;
    virtual Status update(float seconds) = 0;
    virtual void reset() = 0;
};

#endif // ACTION_H
