#include "squaremapnoise.h"

#include "engine/map_generation/valuenoise.h"
#include "engine/map_generation/squareweightfunction.h"
#include "engine/util/util.h"
#include <math.h>

SquareMapNoise::SquareMapNoise(std::shared_ptr<ValueNoise> noise,
                               std::shared_ptr<Environment> environment, float environmentWeight,
                               std::shared_ptr<ValueNoise> environmentTypeNoise,
                               int environmentIndex, float innerSize, float outerSize)
    : MapNoise(noise, environment, environmentWeight),
      m_environmentTypeNoise(environmentTypeNoise),
      m_environmentIndex(environmentIndex),
      m_innerSize(innerSize),
      m_outerSize(outerSize),
      m_environmentChunkSize(outerSize*1.5)
{
}

float SquareMapNoise::getWeight(glm::vec2 point){

    QList<glm::vec2> corners = getCorners(point);
    float weightSum = 0;
    for(glm::vec2 corner : corners){
        if(getIsEnvironmentIndex(corner)){
            glm::vec2 center = glm::vec2(corner.x * m_environmentChunkSize, corner.y * m_environmentChunkSize);
//            std::cout << point << ", " << corner << std::endl;
            std::shared_ptr<SquareWeightFunction> squareFunction = std::make_shared<SquareWeightFunction>(center, m_innerSize, m_outerSize);
            weightSum += squareFunction->getWeight(point);
        }
    }
    return weightSum;
}

QList<glm::vec2> SquareMapNoise::getCorners(glm::vec2 point){
    QList<glm::vec2> corners;

    corners.append(glm::vec2(floor(point.x /m_environmentChunkSize), floor(point.y / m_environmentChunkSize)));
    corners.append(corners.at(0) + glm::vec2(0, 1));
    corners.append(corners.at(0) + glm::vec2(1, 0));
    corners.append(corners.at(0) + glm::vec2(1, 1));
    return corners;
}

bool SquareMapNoise::getIsEnvironmentIndex(glm::vec2 point){
    float y = m_environmentTypeNoise->interpolatedNoise(point);
    int index = static_cast<int>(floor(y)) % 3;
//    std::cout << "y: " << y << ", index: " << index << ", " << (index == m_environmentIndex) << std::endl;
    if(index < 0){
        index = 0;
    }
    assert(index == 0 || index == 1 || index == 2);

    return index == m_environmentIndex;

}
