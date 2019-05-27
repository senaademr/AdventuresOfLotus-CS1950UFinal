#ifndef MOUNTAINENVIRONMENT_H
#define MOUNTAINENVIRONMENT_H

#include "engine/map_generation/environment.h"

class ValueNoise;

class MountainEnvironment : public Environment
{
public:
    MountainEnvironment(unsigned int seed);

    // Environment interface
public:
    std::string getTexture(glm::vec3 position) override;
    std::string getEnvironmentName() override;

private:
    std::shared_ptr<ValueNoise> m_terrainMapNoise;
};

#endif // MOUNTAINENVIRONMENT_H
