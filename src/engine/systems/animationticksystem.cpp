#include "animationticksystem.h"

#include "engine/components/animationcomponent.h"

AnimationTickSystem::AnimationTickSystem():
    TickSystem (TypeID::value<AnimationComponent>())
{

}

void AnimationTickSystem::tick(float seconds){
    for(std::shared_ptr<Component> component : this->getComponents()){
        std::shared_ptr<AnimationComponent> animComponent = std::dynamic_pointer_cast<AnimationComponent>(component);
        if(animComponent){
            animComponent->tick(seconds);
        }
        else{
            std::cout << "Bad component!" << std::endl;
        }
    }

}
