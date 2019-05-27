#ifndef TICKSYSTEM_H
#define TICKSYSTEM_H

#include "engine/systems/system.h"

class TickSystem : public System
{
public:
    TickSystem(size_t componentTypeID);
    TickSystem();
    virtual ~TickSystem();

    virtual void tick(float seconds);
};
#endif // TICKSYSTEM_H
