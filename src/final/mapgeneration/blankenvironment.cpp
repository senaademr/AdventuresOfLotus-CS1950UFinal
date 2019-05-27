#include "blankenvironment.h"

BlankEnvironment::BlankEnvironment()
    : Environment()
{
}



std::string BlankEnvironment::getTexture(glm::vec3 position){
    return "blank";
}

std::string BlankEnvironment::getEnvironmentName(){
    return "blank";
}
