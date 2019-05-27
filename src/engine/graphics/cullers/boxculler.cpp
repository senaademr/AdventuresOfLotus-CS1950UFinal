#include "boxculler.h"

#include "cullmath.h"
#include "engine/components/transformcomponent.h"

BoxCuller::BoxCuller(std::shared_ptr<TransformComponent> transform)
    : Culler(transform)
{
}

bool BoxCuller::shouldCull(QList<glm::vec4> &planes){
    auto corners = getCorners();
    return CullMath::shouldCullCorners(planes, corners);

}

QList<glm::vec4> BoxCuller::getCorners(){
    QList<glm::vec4> corners;
    Transform transform = m_transform->getTransform();
    glm::vec3 pos = transform.getPosition();
    glm::vec3 size = transform.getSize();

    for(glm::vec3 mult : getMultipliers()){
        glm::vec3 corner = pos + size * mult;
        corners.append(glm::vec4(corner, 1));
    }
    assert(corners.size() == 8);
    return corners;
}



