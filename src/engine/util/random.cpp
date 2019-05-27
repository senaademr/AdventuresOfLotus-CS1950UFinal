#include "random.h"

#include <iostream>

void Random::setSeed(unsigned int seed){
    srand(seed);
}

/**
 * @brief Random::randBetween returns a number between min and max (inclusive)
 * @param min
 * @param max
 * @return
 */
int Random::randBetweenInclusive(int min, int max){
    if(min > max){
        std::cout << "min is not less than max in rand between. min: " << min << ", max: " << max << std::endl;
        throw -1;
    }
    int dif = (max+1)-min;
    return rand() % dif + min;
}

int Random::randBetweenExclusive(int min, int max){
    return randBetweenInclusive(min, max-1);
}

int Random::randBetweenInclusive(glm::ivec2 range){
    return randBetweenInclusive(range.x, range.y);
}
