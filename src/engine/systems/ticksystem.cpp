#include "ticksystem.h"

#include "engine/components/tickable.h"
#include "engine/util/util.h"

TickSystem::TickSystem(size_t componentTypeID) : System(componentTypeID)
{

}

TickSystem::TickSystem() :System() {

}
TickSystem::~TickSystem(){}

void TickSystem::tick(float seconds){
    for(std::shared_ptr<Component> component : this->getComponents()){
        std::shared_ptr<Tickable> tickComponent = std::dynamic_pointer_cast<Tickable>(component);
        if(tickComponent){
            tickComponent->tick(seconds);
        }
        else{
            std::cout << "untickable component in tickSystem " << std::endl;
        }
    }
}
