#ifndef ANIMATIONTICKSYSTEM_H
#define ANIMATIONTICKSYSTEM_H

#include "ticksystem.h"

class AnimationTickSystem : public TickSystem
{
public:
    AnimationTickSystem();
    void tick(float seconds) override;
};

#endif // ANIMATIONTICKSYSTEM_H
