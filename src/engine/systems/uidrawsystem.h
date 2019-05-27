#ifndef UIDRAWSYSTEM_H
#define UIDRAWSYSTEM_H

#include "drawsystem.h"
#include "ticksystem.h"

class UIDrawSystem : public DrawSystem
{
public:
    UIDrawSystem(std::shared_ptr<Camera> camera);

    // DrawSystem interface
public:
    void draw() override;

};

#endif // UIDRAWSYSTEM_H
