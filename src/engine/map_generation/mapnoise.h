#ifndef MAPNOISE_H
#define MAPNOISE_H

#include "engine/util/CommonIncludes.h"
#include <QList>

class ValueNoise;
class Environment;
class WeightFunction;

class MapNoise
{
public:
    MapNoise(std::shared_ptr<ValueNoise> noise, std::shared_ptr<Environment> environment, float environmentWeight);

    void setSeed(unsigned int seed);
    float interpolatedNoise(glm::vec2 point);

    std::string getEnvironmentName();
    std::string getTexture(glm::vec3 point);
    virtual float getWeight(glm::vec2 point);

    float getEnvironmentWeight(glm::vec2 point);

    void addWeightFunction(std::shared_ptr<WeightFunction> functionToAdd);
protected:

    std::shared_ptr<ValueNoise> m_noise;
    std::shared_ptr<Environment> m_environment;

private:
    QList<std::shared_ptr<WeightFunction> > m_weightFunctions;
    std::shared_ptr<ValueNoise> m_environmentNoise;
    float m_environmentWeight;
};

#endif // MAPNOISE_H
