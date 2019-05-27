#ifndef SQUAREMAPNOISE_H
#define SQUAREMAPNOISE_H

#include "engine/map_generation/mapnoise.h"

class SquareMapNoise : public MapNoise
{
public:
    SquareMapNoise(std::shared_ptr<ValueNoise> noise, std::shared_ptr<Environment> environment,
                   float environmentWeight, std::shared_ptr<ValueNoise> environmentTypeNoise,
                   int environmentIndex, float innerSize, float outerSize);

    // MapNoise interface
public:
    float getWeight(glm::vec2 point) override;

private:
    bool getIsEnvironmentIndex(glm::vec2 point);
    QList<glm::vec2> getCorners(glm::vec2 point);

    std::shared_ptr<ValueNoise> m_environmentTypeNoise;
    int m_environmentIndex;
    float m_innerSize;
    float m_outerSize;
    float m_environmentChunkSize;

};

#endif // SQUAREMAPNOISE_H
