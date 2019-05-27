#include "system.h"

System::System(size_t componentTypeID) {
    m_componentTypeIDs.append(componentTypeID);
}

System::System(){

}
void System::addType(size_t componentTypeID){
    if(!m_components.isEmpty()){
        std::cout << "Warning: adding types after components already in system" << std::endl;
    }
    m_componentTypeIDs.append(componentTypeID);
}
QList<std::shared_ptr<Component>> System::getComponents(){
    return m_components;
}


bool System::hasComponentTypeID(size_t componentTypeID){
    return m_componentTypeIDs.contains(componentTypeID);
}

void System::addComponent(std::shared_ptr<Component> component, size_t componentTypeID){
    if(hasComponentTypeID(componentTypeID) ){
        m_components.append(component);
    }
    else{
        std::cout << "Trying to add bad component" << std::endl;
        throw -1;
    }
}

//void System::addComponent(std::shared_ptr<Component> component){
//    if(hasComponentType(component->COMPONENT_TYPE) ){
//        m_components.append(component);
//    }
//    else{
//        std::cout << "Trying to add bad component" << std::endl;
//        throw -1;
//    }
//}

void System::removeComponent(std::shared_ptr<Component> component){
    m_components.removeOne(component);
}
