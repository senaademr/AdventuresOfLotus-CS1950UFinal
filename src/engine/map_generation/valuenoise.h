#ifndef VALUENOISE_H
#define VALUENOISE_H

//https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/procedural-patterns-noise-part-1

#include "engine/util/CommonIncludes.h"
#include "noisefunction.h"
#include <random>

class ValueNoise : public NoiseFunction
{
public:
    ValueNoise(unsigned int seed = 2016);

    void setSeed(unsigned int seed);
    void setAmplitude(float amplitude);
    void setFrequency(float frequency);
    void setOctaves(int octaves);
    void setYShift(float shift);

    float interpolatedNoise(glm::vec2 point) override;
    glm::vec3 interpolatedNoiseToVec(const glm::vec2 &vec) override;

    static float linearInterpolation(const float &a, const float &b, const float &t);
    static float smoothInterpolation(const float &a, const float &b, const float &t);
    static float perlinInterpolation(const float &a, const float &b, const float &t);


private:

    float noise(int x, int y, unsigned int seed);
    float valueNoise(glm::ivec2 point, unsigned int seed);
    float interpolatedNoiseHelper(glm::vec2 point, unsigned int seed);

    unsigned int m_seed;
    float m_amplitude;
    float m_frequency;
    int m_octaves;
    float m_yShift;

    std::default_random_engine m_generator;

    std::uniform_real_distribution<float> m_distribution;




};

#endif // VALUENOISE_H
