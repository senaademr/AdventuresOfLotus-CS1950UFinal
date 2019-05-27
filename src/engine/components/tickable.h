#ifndef TICKABLE_H
#define TICKABLE_H

class Tickable
{
public:
    virtual void tick(float seconds) = 0;
};

#endif // TICKABLE_H
