#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "engine/util/CommonIncludes.h"

class Environment
{
public:
    virtual std::string getTexture(glm::vec3 position) = 0;
    virtual std::string getEnvironmentName() = 0 ;

};

#endif // ENVIRONMENT_H
