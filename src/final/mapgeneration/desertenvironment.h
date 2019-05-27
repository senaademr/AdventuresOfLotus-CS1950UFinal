#ifndef DESERTENVIRONMENT_H
#define DESERTENVIRONMENT_H

#include "engine/map_generation/environment.h"

class DesertEnvironment : public Environment
{
public:
    DesertEnvironment();

    // Environment interface
public:
    std::string getTexture(glm::vec3 position) override;
    std::string getEnvironmentName() override;
};

#endif // DESERTENVIRONMENT_H
