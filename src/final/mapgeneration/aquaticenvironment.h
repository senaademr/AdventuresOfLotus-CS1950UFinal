#ifndef AQUATICENVIRONMENT_H
#define AQUATICENVIRONMENT_H

#include "engine/map_generation/environment.h"

class ValueNoise;

class AquaticEnvironment : public Environment
{
public:
    AquaticEnvironment(unsigned int seed);

    // Environment interface
public:
    std::string getTexture(glm::vec3 position) override;
    std::string getEnvironmentName() override;
private:

    std::shared_ptr<ValueNoise> m_terrainMapNoise;
};

#endif // AQUATICENVIRONMENT_H
