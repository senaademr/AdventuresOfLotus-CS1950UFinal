#include "animationdrawsystem.h"

#include "engine/components/animationcomponent.h"

AnimationDrawSystem::AnimationDrawSystem(std::shared_ptr<Camera> camera):
    DrawSystem(camera, TypeID::value<AnimationComponent>())
{

}

void AnimationDrawSystem::draw(){
    for(std::shared_ptr<Component> component : this->getComponents()){
        std::shared_ptr<AnimationComponent> animComponent = std::dynamic_pointer_cast<AnimationComponent>(component);
        if(animComponent){
            animComponent->draw();
        }
        else{
            std::cout << "Bad component!" << std::endl;
        }
    }

}
