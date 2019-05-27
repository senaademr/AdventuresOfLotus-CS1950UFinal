#ifndef SEQUENCE_H
#define SEQUENCE_H
#include "composite.h"
/**
 * @brief The Sequence class
 * Sequences start updating from the previously RUNNING child
 * Previously running child should be left intact after returning, unless the entire sequence was completed
 * Goal is to complete the entire sequence – “I was in the middle of something and should continue where I left off”
 */
class Sequence : public Composite
{
public:
    Sequence(std::map<std::string, std::string> &blackboard);
    ~Sequence() override;
    Status update(float seconds) override;
    void reset() override;
};

#endif // SEQUENCE_H
