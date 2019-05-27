#include "mountainenvironment.h"

#include "engine/map_generation/valuenoise.h"

MountainEnvironment::MountainEnvironment(unsigned int seed)
    : Environment(),
      m_terrainMapNoise(nullptr)
{
    m_terrainMapNoise = std::make_shared<ValueNoise>(seed);
    m_terrainMapNoise->setFrequency(.6);
    m_terrainMapNoise->setAmplitude(7);
}


std::string MountainEnvironment::getTexture(glm::vec3 position){

    float textureNoiseOffset = m_terrainMapNoise->interpolatedNoise(glm::vec2(position.x, position.z));
    std::string textureName = "";
    if(position.y + .2f*textureNoiseOffset< 5){
        textureName = "grass";
    }
    else if(position.y + textureNoiseOffset < 20){
        textureName = "stone";
    }
    else{
        textureName = "snow";
    }
    return textureName;

}


std::string MountainEnvironment::getEnvironmentName(){
    return "mountain";
}

