#include "component.h"


Component::Component() :
    m_gameObject(nullptr)

{
}

Component::~Component(){}

std::shared_ptr<GameObject> Component::getGameObject(){
    return m_gameObject;
}

void Component::setGameObject(std::shared_ptr<GameObject> gameObject){
    m_gameObject = gameObject;
}
