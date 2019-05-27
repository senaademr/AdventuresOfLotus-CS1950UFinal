#include "chunkculler.h"

#include "cullmath.h"
#include "engine/components/transformcomponent.h"

ChunkCuller::ChunkCuller(std::shared_ptr<TransformComponent> transform)
    : Culler(transform)
{
}

bool ChunkCuller::shouldCull(QList<glm::vec4> &planes){
    auto corners = getCorners();
    return CullMath::shouldCullCorners(planes, corners);
}


//TODO: make chunk not tall
QList<glm::vec4> ChunkCuller::getCorners(){
    QList<glm::vec4> corners;
    Transform transform = m_transform->getTransform();
    glm::vec3 pos = transform.getPosition();
    glm::vec3 size = transform.getSize();
    size = glm::vec3(size.x, size.y/size.x, size.z);

    for(glm::vec3 mult : getMultipliers()){
        glm::vec3 corner = pos + size * mult;
        corners.append(glm::vec4(corner, 1));
    }
    assert(corners.size() == 8);
    return corners;
}
