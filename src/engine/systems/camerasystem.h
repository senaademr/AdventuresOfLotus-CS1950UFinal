#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "ticksystem.h"

class CameraSystem : public TickSystem
{
public:
    CameraSystem();
    ~CameraSystem() override;

    // TickSystem interface
public:
    void tick(float seconds);
};

#endif // CAMERASYSTEM_H
