#include "aquaticenvironment.h"

#include "engine/map_generation/valuenoise.h"

AquaticEnvironment::AquaticEnvironment(unsigned int seed)
{
    m_terrainMapNoise = std::make_shared<ValueNoise>(seed);
    m_terrainMapNoise->setFrequency(.1);
    m_terrainMapNoise->setAmplitude(4);
}



std::string AquaticEnvironment::getTexture(glm::vec3 position){
    float textureNoiseOffset = m_terrainMapNoise->interpolatedNoise(glm::vec2(position.x, position.z));
    std::string textureName = "";
    if(position.y + textureNoiseOffset< -2){
        textureName = "water";
    }
    else{
        textureName = "sand";
    }
    return textureName;
}


std::string AquaticEnvironment::getEnvironmentName(){
    return "aquatic";
}
