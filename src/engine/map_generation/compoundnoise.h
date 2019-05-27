#ifndef COMPOUNDNOISE_H
#define COMPOUNDNOISE_H

#include "engine/util/CommonIncludes.h"
#include "noisefunction.h"
#include <QList>

class MapNoise;

class CompoundNoise : public NoiseFunction
{
public:
    CompoundNoise(unsigned int seed);
    void addNoiseFunction(std::shared_ptr<MapNoise> noiseFunction);

    std::string getTextureAtlasName(const glm::vec3 &point);
    std::string getEnvironment(const glm::vec3 &point);
    float interpolatedNoise(glm::vec2 point) override;
    glm::vec3 interpolatedNoiseToVec(const glm::vec2 &vec) override;

private:
    unsigned int m_startingSeed;
    QList<std::shared_ptr<MapNoise> > m_noiseFunctions;
};

#endif // COMPOUNDNOISE_H
