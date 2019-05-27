#include "compoundnoise.h"

#include "mapnoise.h"
#include <math.h>

CompoundNoise::CompoundNoise(unsigned int seed)
    : m_startingSeed(seed)
{
}


void CompoundNoise::addNoiseFunction(std::shared_ptr<MapNoise> noiseFunction){
    unsigned int newFunctionSeed = m_startingSeed + (m_noiseFunctions.size() * 7.f);
    noiseFunction->setSeed(newFunctionSeed);
    m_noiseFunctions.append(noiseFunction);
}


std::string CompoundNoise::getTextureAtlasName(const glm::vec3 &point){
    if(m_noiseFunctions.isEmpty()){
        std::cout << "Warning: cant get material with no noise functions";
        return "default";
    }
    glm::vec2 pointTwoD = glm::vec2(point.x, point.z);

    float bestWeight = m_noiseFunctions.at(0)->getEnvironmentWeight(pointTwoD);
    std::string bestTexture = m_noiseFunctions.at(0)->getTexture(point);
//    std::cout << "curWeight: "<< bestWeight << ", texture: " << bestTexture << std::endl;
    for(int i = 1; i < m_noiseFunctions.size(); i ++){
        std::shared_ptr<MapNoise> noiseFunction = m_noiseFunctions.at(i);
        float curWeight = noiseFunction->getEnvironmentWeight(pointTwoD);
//        std::cout << "curWeight: "<< curWeight << ", texture: " << noiseFunction->getTexture(point) << std::endl;
        if(curWeight > bestWeight){
            bestWeight = curWeight;
            bestTexture = noiseFunction->getTexture(point);
        }
    }
//    std::cout << "returning texture: " << bestTexture << std::endl;
    return bestTexture;
}

std::string CompoundNoise::getEnvironment(const glm::vec3 &point){
    if(m_noiseFunctions.isEmpty()){
        std::cout << "Warning: cant get environment with no noise functions";
        return "default";
    }
    glm::vec2 pointTwoD = glm::vec2(point.x, point.z);

    float bestWeight = m_noiseFunctions.at(0)->getEnvironmentWeight(pointTwoD);
    std::string bestEnvironment = m_noiseFunctions.at(0)->getEnvironmentName();
    for(int i = 1; i < m_noiseFunctions.size(); i ++){
        std::shared_ptr<MapNoise> noiseFunction = m_noiseFunctions.at(i);
        float curWeight = noiseFunction->getEnvironmentWeight(pointTwoD);
        if(curWeight > bestWeight){
            bestWeight = curWeight;
            bestEnvironment = noiseFunction->getEnvironmentName();
        }
    }
    return bestEnvironment;
}

float CompoundNoise::interpolatedNoise(glm::vec2 point){
    if(m_noiseFunctions.isEmpty()){
        std::cout << "Warning: interpolated with no noise functions";
        return -10;
    }
    float compoundedY = 0;
    float totalWeight = 0;
    for(std::shared_ptr<MapNoise> noiseFunction : m_noiseFunctions){
        float weight = noiseFunction->getWeight(point);
        float y = noiseFunction->interpolatedNoise(point);
        float weightModified = weight;
        compoundedY += weightModified * y;
        totalWeight += weightModified;
    }
    float result = compoundedY / totalWeight;
    if(isnan(result)){
        std::cout << "result is nan" << std::endl;
    }
    return compoundedY / totalWeight;

}

glm::vec3 CompoundNoise::interpolatedNoiseToVec(const glm::vec2 &vec){
    float y = interpolatedNoise(vec);
    return glm::vec3(vec.x, y, vec.y);
}
