#ifndef BLANKENVIRONMENT_H
#define BLANKENVIRONMENT_H

#include "engine/map_generation/environment.h"

class BlankEnvironment : public Environment
{
public:
    BlankEnvironment();

    // Environment interface
public:
    std::string getTexture(glm::vec3 position) override;

    std::string getEnvironmentName() override;

};

#endif // BLANKENVIRONMENT_H
