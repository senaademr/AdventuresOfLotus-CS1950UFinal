#include "gameworld.h"

#include "engine/systems/uidrawsystem.h"
#include "engine/systems/uiticksystem.h"

#include "engine/systems/objectdrawsystem.h"
#include "engine/systems/animationdrawsystem.h"
#include "engine/basics/gameobject.h"

GameWorld::GameWorld(std::shared_ptr<Camera> camera)
    : m_defaultDrawSystem(nullptr),
      m_defaultTickSystem(nullptr),
      m_uiDrawSystem(nullptr),
      m_uiTickSystem(nullptr)
{
    m_defaultDrawSystem = std::make_shared<AnimationDrawSystem>(camera);
    m_defaultTickSystem = std::make_shared<TickSystem>();
    m_uiDrawSystem = std::make_shared<UIDrawSystem>(camera);
    m_uiTickSystem = std::make_shared<UITickSystem>();
    addDrawSystem(m_defaultDrawSystem);
    m_defaultDrawSystem = std::make_shared<ObjectDrawSystem>(camera);
    addDrawSystem(m_defaultDrawSystem);
    addTickSystem(m_defaultTickSystem);
    addDrawSystem(m_uiDrawSystem);
    addTickSystem(m_uiTickSystem);

}

void GameWorld::addDrawSystem(std::shared_ptr<DrawSystem> drawSystem){
    m_drawSystems.append(drawSystem);
    for(std::shared_ptr<GameObject> object : m_gameObjects){
        addToSystemIfNeccessary(drawSystem, object);
    }
}

void GameWorld::removeDrawSystem(std::shared_ptr<DrawSystem> drawSystem){
    m_drawSystems.removeOne(drawSystem);
}

void GameWorld::addTickSystem(std::shared_ptr<TickSystem> tickSystem){
    m_tickSystems.append(tickSystem);
    for(std::shared_ptr<GameObject> object : m_gameObjects){
        addToSystemIfNeccessary(tickSystem, object);
    }
}

//void GameWorld::addTickSystemType(ComponentType type){

//}

void GameWorld::removeTickSystem(std::shared_ptr<TickSystem> tickSystem){
    m_tickSystems.removeOne(tickSystem);
}

void GameWorld::addObject(std::shared_ptr<GameObject> object){
    m_gameObjects.append(object);
    for(size_t componentTypeID : object->getKeys()){

        for(std::shared_ptr<DrawSystem> drawSystem : m_drawSystems){
            addToSystemIfNeccessary(drawSystem, object, componentTypeID);
        }
        for(std::shared_ptr<TickSystem> tickSystem : m_tickSystems){
            addToSystemIfNeccessary(tickSystem, object, componentTypeID);
        }
        addToSystemIfNeccessary(m_uiDrawSystem, object, componentTypeID);
        addToSystemIfNeccessary(m_uiTickSystem, object, componentTypeID);

//        if(m_uiDrawSystem->hasComponentType(componentType)){
//            m_uiDrawSystem->addComponent(object->getComponent<Component>(componentType));
//        }
//        if(m_uiTickSystem->hasComponentType(componentType)){
//            m_uiTickSystem->addComponent(object->getComponent<Component>(componentType));
//        }
    }
}

void GameWorld::removeObject(std::shared_ptr<GameObject> object){

    m_toRemove.append(object);

}

void GameWorld::removeObjectsFromGame(){
    for(std::shared_ptr<GameObject> object : m_toRemove){
        m_gameObjects.removeOne(object);
        for(size_t componentTypeID : object->getKeys()){
            for(std::shared_ptr<DrawSystem> drawSystem : m_drawSystems){
                if(drawSystem->hasComponentTypeID(componentTypeID)){
                    drawSystem->removeComponent(object->getComponent(componentTypeID));
                }
            }

            for(std::shared_ptr<TickSystem> tickSystem : m_tickSystems){
                if(tickSystem->hasComponentTypeID(componentTypeID)){
                    tickSystem->removeComponent(object->getComponent(componentTypeID));
                }
            }
            if(m_uiDrawSystem->hasComponentTypeID(componentTypeID)){
                m_uiDrawSystem->removeComponent(object->getComponent(componentTypeID));
            }
            if(m_uiTickSystem->hasComponentTypeID(componentTypeID)){
                m_uiTickSystem->removeComponent(object->getComponent(componentTypeID));
            }
        }
    }
    m_toRemove.clear();
}

void GameWorld::addToSystemIfNeccessary(std::shared_ptr<System> system, std::shared_ptr<GameObject> object){
    for(size_t componentTypeID : object->getKeys()){
        addToSystemIfNeccessary(system, object, componentTypeID);
    }
}

void GameWorld::addToSystemIfNeccessary(std::shared_ptr<System> system, std::shared_ptr<GameObject> object, size_t componentTypeID){
    if(system->hasComponentTypeID(componentTypeID) && object->getKeys().contains(componentTypeID)){
        std::shared_ptr<Component> comp = object->getComponent(componentTypeID);
        system->addComponent(comp, componentTypeID);
    }

}
void GameWorld::paintGL(){
    //std::cout << "paint" << std::endl;
    for(std::shared_ptr<DrawSystem> drawSystem : m_drawSystems){
        drawSystem->draw();
    }

    m_uiDrawSystem->draw();
    //drawsystems draw
}
void GameWorld::tick(float seconds){
    //std::cout << "tick" << std::endl;
    for(std::shared_ptr<TickSystem> tickSystem : m_tickSystems){
        tickSystem->tick(seconds);
    }
    assert(m_uiTickSystem);
    m_uiTickSystem->tick(seconds);
    //tick systems tick
    removeObjectsFromGame();
}
