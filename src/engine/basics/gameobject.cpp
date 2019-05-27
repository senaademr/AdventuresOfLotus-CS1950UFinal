#include "gameobject.h"

#include "engine/components/transformcomponent.h"

GameObject::GameObject()
{

}

//void GameObject::addComponent(std::shared_ptr<Component> component){
//    if(hasComponent(component->COMPONENT_TYPE)){
//        std::cout << "Warning: replacing a component" << std::endl;
//    }
//    m_components.insert(component->COMPONENT_TYPE, component);
//}



//bool GameObject::hasComponent(ComponentType componentType){
//    return m_components.contains(componentType);
//}
//void GameObject::removeComponent(std::shared_ptr<Component> component){
//    if(!hasComponent(component->COMPONENT_TYPE)){
//        std::cout << "trying to remove a component that is not in" << std::endl;
//        return;
//    }
//    m_components.remove(component->COMPONENT_TYPE);


//}


std::shared_ptr<Component> GameObject::getComponent(size_t id){
    if(!m_components.contains(id)){
        std::cout << "no component of the requested type: " << id << std::endl;
        throw -1;
    }
    std::shared_ptr<Component> component = m_components.value(id);
    return component;
}


bool GameObject::hasComponent(size_t id){
    return m_components.contains(id);
}

QList<size_t> GameObject::getKeys(){
    return m_components.keys();
}
