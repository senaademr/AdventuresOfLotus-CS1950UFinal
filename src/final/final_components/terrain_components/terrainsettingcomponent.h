#ifndef TERRAINSETTINGCOMPONENT_H
#define TERRAINSETTINGCOMPONENT_H

#include "engine/components/component.h"
#include "engine/components/tickable.h"

class NoiseFunction;
//debugging component that sets the y component of the object to the noise value of the terrain

class TerrainSettingComponent : public Component, public Tickable
{
public:
    TerrainSettingComponent();
    void setNoise(std::shared_ptr<NoiseFunction> noise);

    // Tickable interface
public:
    void tick(float seconds);

private:

    std::shared_ptr<NoiseFunction> m_noise;
};

#endif // TERRAINSETTINGCOMPONENT_H
