#ifndef CONDITION_H
#define CONDITION_H
#include "btnode.h"

class Condition : public BTNode
{
public:
    Condition(std::map<std::string, std::string> &blackboard);
    ~Condition() override;
    virtual Status update(float seconds) = 0;
    virtual void reset() = 0;
};

#endif // CONDITION_H
