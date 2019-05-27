#ifndef UITICKSYSTEM_H
#define UITICKSYSTEM_H

#include "ticksystem.h"

class UITickSystem : public TickSystem
{
public:
    UITickSystem();

    // TickSystem interface
public:
    void tick(float seconds);
};

#endif // UITICKSYSTEM_H
