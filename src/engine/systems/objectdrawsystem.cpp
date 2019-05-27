#include "objectdrawsystem.h"

#include "engine/graphics/Graphics.h"
#include "engine/components/drawable.h"
#include "engine/components/objectdrawcomponent.h"
#include "engine/components/uicomponent.h"
#include "engine/components/animationcomponent.h"
#include "engine/util/CommonIncludes.h"
#include "engine/basics/gameobject.h"
#include "engine/components/transformcomponent.h"
#include "engine/graphics/Shape.h"
#include "engine/graphics/Camera.h"

ObjectDrawSystem::ObjectDrawSystem(std::shared_ptr<Camera> camera) : DrawSystem(camera, TypeID::value<ObjectDrawComponent>())
{
}



void ObjectDrawSystem::draw(){
   // std::cout << "drawing system" << std::endl;
    QList<glm::vec4> planes = calculateCullInfo();
    for(std::shared_ptr<Component> component : this->getComponents()){
        std::shared_ptr<ObjectDrawComponent> drawComponent = std::dynamic_pointer_cast<ObjectDrawComponent>(component);
        if(drawComponent){
            if(!drawComponent->shouldCull(planes)){
                drawComponent->draw();
            }
        }
        else{
            std::cout << "Bad component!" << std::endl;
        }
        //DrawComponent* drawComponent = std::dynamic_cast<DrawComponent*>(component.get());
        std::shared_ptr<AnimationComponent> aniComponent = std::dynamic_pointer_cast<AnimationComponent>(component);
        if(aniComponent){
            aniComponent->draw();
        }
    }

}


QList<glm::vec4> ObjectDrawSystem::calculateCullInfo(){
    glm::mat4x4 frustrum = m_camera->getFrustrum();
    glm::vec4 r0 = glm::vec4(frustrum[0][0], frustrum[1][0], frustrum[2][0], frustrum[3][0]);
    glm::vec4 r1 = glm::vec4(frustrum[0][1], frustrum[1][1], frustrum[2][1], frustrum[3][1]);
    glm::vec4 r2 = glm::vec4(frustrum[0][2], frustrum[1][2], frustrum[2][2], frustrum[3][2]);
    glm::vec4 r3 = glm::vec4(frustrum[0][3], frustrum[1][3], frustrum[2][3], frustrum[3][3]);

    QList<glm::vec4> planes;

    planes.append(r3 - r0);
    planes.append(r3-r1);
    planes.append(r3-r2);

    planes.append(r3  + r0);
    planes.append(r3 + r1);
    planes.append(r3 + r2);

    return planes;

}
