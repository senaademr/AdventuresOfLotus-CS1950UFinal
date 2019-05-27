#include "cullmath.h"


bool CullMath::shouldCullCorners(QList<glm::vec4> &planes, QList<glm::vec4> corners){
    assert(planes.size() == 6);
    //std::cout << "testing should cull" << std::endl;
    for(glm::vec4 plane : planes){
        if(cullPlane(plane, corners)){
            //std::cout << "culling" << std::endl;
            return true;
        }
    }
    //std::cout << "not culling" << std::endl;
    return false;
}

bool CullMath::cullPlane(glm::vec4 &plane, QList<glm::vec4> &corners){
    for(glm::vec4 corner :corners ){
        if(glm::dot(plane, corner) >= 0){
            return false;
        }
    }
    return true;
}
