#include "uidrawsystem.h"

#include "engine/components/uicomponent.h"

UIDrawSystem::UIDrawSystem(std::shared_ptr<Camera> camera) :
    DrawSystem(camera, TypeID::value<UIComponent>())
{
}



void UIDrawSystem::draw(){
//    std::cout << "drawing ui" << std::endl;
    for(std::shared_ptr<Component> component : this->getComponents()){
        std::shared_ptr<UIComponent> uiComponent = std::dynamic_pointer_cast<UIComponent>(component);

        if(uiComponent){
            uiComponent->draw();
        }
        else{
            std::cout << "Bad component!" << std::endl;
        }
        //DrawComponent* drawComponent = std::dynamic_cast<DrawComponent*>(component.get());
    }

}



