#ifndef ANIMATIONDRAWSYSTEM_H
#define ANIMATIONDRAWSYSTEM_H

#include "drawsystem.h"

class AnimationDrawSystem : public DrawSystem
{
public:
    AnimationDrawSystem(std::shared_ptr<Camera> camera);
    void draw() override;
};

#endif // ANIMATIONDRAWSYSTEM_H
