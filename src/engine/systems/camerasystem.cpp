#include "camerasystem.h"

#include "engine/components/cameracomponent.h"

CameraSystem::CameraSystem()
    :TickSystem(TypeID::value<CameraComponent>())
{
}

CameraSystem::~CameraSystem(){

}

void CameraSystem::tick(float seconds){
    for(std::shared_ptr<Component> component : this->getComponents()){
        std::shared_ptr<CameraComponent> camera = std::dynamic_pointer_cast<CameraComponent>(component);

        if(camera){
            camera->tick(seconds);
        }
        else{
            std::cout << "Bad camera!" << std::endl;
        }
        //DrawComponent* drawComponent = std::dynamic_cast<DrawComponent*>(component.get());
    }

}
