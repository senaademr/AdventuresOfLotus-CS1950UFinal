#include "mapnoise.h"

#include "valuenoise.h"
#include "engine/map_generation/environment.h"
#include "engine/map_generation/weightfunction.h"

MapNoise::MapNoise(std::shared_ptr<ValueNoise> noise, std::shared_ptr<Environment> environment, float environmentWeight)
      : m_noise(noise),
        m_environment(environment),
        m_environmentWeight(environmentWeight)
{
    m_environmentNoise = std::make_shared<ValueNoise>();
    m_environmentNoise->setAmplitude(3);
    m_environmentNoise->setFrequency(.2);
}

void MapNoise::setSeed(unsigned int seed){
    m_noise->setSeed(seed);
}

float MapNoise::interpolatedNoise(glm::vec2 point){
    return m_noise->interpolatedNoise(point);
}


std::string MapNoise::getTexture(glm::vec3 point){
    return m_environment->getTexture(point);
}

float MapNoise::getWeight(glm::vec2 point){
    float totalWeight = 0;
    for(std::shared_ptr<WeightFunction> weightFunction : m_weightFunctions){
        totalWeight += weightFunction->getWeight(point);
    }
    return totalWeight;
}

void MapNoise::addWeightFunction(std::shared_ptr<WeightFunction> functionToAdd){
    m_weightFunctions.append(functionToAdd);
}

float MapNoise::getEnvironmentWeight(glm::vec2 point){
    return (m_environmentWeight +m_environmentNoise->interpolatedNoise(point)) * getWeight(point);
}


std::string MapNoise::getEnvironmentName(){
    return m_environment->getEnvironmentName();
}
