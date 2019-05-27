#include "valuenoise.h"

#include <glm/glm.hpp>


ValueNoise::ValueNoise(unsigned int seed)
    : m_seed(seed),
      m_amplitude(1.f),
      m_frequency(1.f),
      m_octaves(1),
      m_yShift(1),
      m_generator(),
      m_distribution(-.5f, .5f)
{
}

//return m_amplitude* (-.5f + 1.f * glm::fract(sin(x * 127.1f + y * 311.7f+ (seed %3727 ) * 473.73f) * (43758.5453123f)));

//given by tyler schicke
float ValueNoise::noise(int x, int y, unsigned int seed){
    unsigned int seedValue = seed % 109;
    int n = x + y * 43 + seedValue * 47;
    n = (n << 13) ^ n;
    int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
    return (m_amplitude *(1.0 - ((double) nn / 1073741824.0))) + m_yShift;

}

float ValueNoise::valueNoise(glm::ivec2 point, unsigned int seed){
    float corners = noise(point.x-1, point.y-1, seed)
                    + noise(point.x-1, point.y +1, seed)
                    + noise(point.x+1, point.y-1, seed)
                    + noise(point.x +1, point.y +1, seed);
    corners /= 16.f;

    float sides = noise(point.x -1, point.y, seed)
                    + noise(point.x, point.y-1, seed)
                    + noise(point.x +1, point.y, seed)
                    + noise(point.x, point.y +1, seed);
    sides/= 8.f;

    float center = noise(point.x, point.y, seed)/ 4;
    return center + sides + corners;
}

float ValueNoise::interpolatedNoise(glm::vec2 point){
    float amplitude = 1.f;
    float frequency = 1.f;
    float total = 0;
    for(int i = 0; i < m_octaves; i ++){
        total += amplitude * interpolatedNoiseHelper(point * frequency, m_seed + 11*i);
        amplitude /= 2.f;
        frequency *= 2.f;
    }
    return total;
}


float ValueNoise::interpolatedNoiseHelper(glm::vec2 point, unsigned int seed){
    glm::vec2 pointFrequency = m_frequency * point;
    glm::ivec2 topLeft = glm::ivec2(std::floor(pointFrequency.x), std::floor(pointFrequency.y));
    glm::ivec2 topRight = glm::ivec2(std::floor(pointFrequency.x+1), std::floor(pointFrequency.y));
    glm::ivec2 bottomLeft = glm::ivec2(std::floor(pointFrequency.x), std::floor(pointFrequency.y+1));
    glm::ivec2 bottomRight = glm::ivec2(std::floor(pointFrequency.x+1), std::floor(pointFrequency.y+1));

    float dx = pointFrequency.x - std::floor(pointFrequency.x);
    float dy = pointFrequency.y - std::floor(pointFrequency.y);

    float topNoise = perlinInterpolation(valueNoise(topLeft, seed), valueNoise(topRight, seed), dx);
    float bottomNoise = perlinInterpolation(valueNoise(bottomLeft, seed), valueNoise(bottomRight, seed), dx);

    float result = perlinInterpolation(topNoise, bottomNoise, dy);
    return result;
}



void ValueNoise::setSeed(unsigned int seed){
    m_seed = seed;
}

void ValueNoise::setAmplitude(float amplitude){
    m_amplitude = amplitude;
}

void ValueNoise::setFrequency(float frequency){
    m_frequency = frequency;
}

void ValueNoise::setOctaves(int octaves){
    m_octaves = octaves;
}

void ValueNoise::setYShift(float shift){
    m_yShift = shift;

}

glm::vec3 ValueNoise::interpolatedNoiseToVec(const glm::vec2 &vec){
    float y = interpolatedNoise(vec);
    return glm::vec3(vec.x, y, vec.y);
}


float ValueNoise::linearInterpolation(const float &a, const float &b, const float &t){
    return a * (1.f-t) + b* t;
}
float ValueNoise::smoothInterpolation(const float &a, const float &b, const float &t){
    float tStar = 3.f * t*t -2.f*t*t*t;
    return linearInterpolation(a, b, tStar);
}
float ValueNoise::perlinInterpolation(const float &a, const float &b, const float &t){
    float tStar = 6.f * t*t*t*t*t - 15.f * t*t*t*t + 10.f * t*t*t;
    return linearInterpolation(a, b, tStar);
}
