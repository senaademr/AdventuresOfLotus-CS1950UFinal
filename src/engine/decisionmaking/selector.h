#ifndef SELECTOR_H
#define SELECTOR_H
#include "composite.h"
/**
 * @brief The Selector class
 * Selectors should always update from the first child
 * Should reset the previously running child if a child before it starts RUNNING
 * Children have priority – “I should always go back to defend my base, even if I’m in the middle of an offensive sequence”
 */
class Selector : public Composite
{
public:
    Selector(std::map<std::string, std::string> &blackboard);
    ~Selector() override;
    Status update(float seconds) override;
    void reset() override;
};

#endif // SELECTOR_H
