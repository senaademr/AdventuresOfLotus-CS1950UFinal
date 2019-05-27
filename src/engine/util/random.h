#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>
#include <memory>
#include <glm/glm.hpp>

class Random
{
public:
    static void setSeed(unsigned int seed);
    static int randBetweenInclusive(int min, int max);

    static int randBetweenExclusive(int min, int max);
    static int randBetweenInclusive(glm::ivec2 range);
};

#endif // RANDOM_H
