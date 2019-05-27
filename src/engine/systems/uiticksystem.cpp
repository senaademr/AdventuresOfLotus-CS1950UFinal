#include "uiticksystem.h"

#include "engine/components/uicomponent.h"

UITickSystem::UITickSystem()
    : TickSystem(TypeID::value<UIComponent>())
{
}

void UITickSystem::tick(float seconds){
    for(std::shared_ptr<Component> component : this->getComponents()){
        std::shared_ptr<UIComponent> uiComponent = std::dynamic_pointer_cast<UIComponent>(component);
        if(uiComponent){
            uiComponent->tick(seconds);
        }
        else{
            std::cout << "Bad component!" << std::endl;
        }
    }
}
