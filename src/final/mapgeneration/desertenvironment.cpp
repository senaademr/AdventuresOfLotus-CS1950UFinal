#include "desertenvironment.h"

DesertEnvironment::DesertEnvironment()
    : Environment()
{
}

std::string DesertEnvironment::getTexture(glm::vec3 position){
    return "sand";
}

std::string DesertEnvironment::getEnvironmentName(){
    return "desert";
}
