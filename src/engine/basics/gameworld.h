 #ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QList>

#include "engine/util/CommonIncludes.h"
#include "engine/components/componenttype.h"
#include "engine/basics/typeid.h"

#include "engine/systems/drawsystem.h"
#include "engine/systems/ticksystem.h"

class DrawSystem;
class TickSystem;
class UITickSystem;
class UIDrawSystem;

class GameObject;
class System;
class Camera;

class GameWorld
{
public:
    GameWorld(std::shared_ptr<Camera> camera);

    void paintGL();
    void tick(float seconds);

    void addDrawSystem(std::shared_ptr<DrawSystem> drawSystem);
    void removeDrawSystem(std::shared_ptr<DrawSystem> drawSystem);
    void addTickSystem(std::shared_ptr<TickSystem> tickSystem);
    void removeTickSystem(std::shared_ptr<TickSystem> tickSystem);

    template<class T>
    void addTickSystemType(){
        m_defaultTickSystem->addType(TypeID::value<T>());
//        for(std::shared_ptr<GameObject> object : m_gameObjects){
//            addToSystemIfNeccessary(m_defaultTickSystem, object, type);
//        }
    }

    void addObject(std::shared_ptr<GameObject> object);
    void removeObject(std::shared_ptr<GameObject> object);

private:
    void removeObjectsFromGame();
    void addToSystemIfNeccessary(std::shared_ptr<System> system, std::shared_ptr<GameObject> object);
    void addToSystemIfNeccessary(std::shared_ptr<System> system, std::shared_ptr<GameObject> object, size_t componentTypeID);

private:
    QList<std::shared_ptr<GameObject> > m_gameObjects;
    std::shared_ptr<DrawSystem> m_defaultDrawSystem;
    std::shared_ptr<TickSystem> m_defaultTickSystem;

    std::shared_ptr<UIDrawSystem> m_uiDrawSystem;
    std::shared_ptr<UITickSystem> m_uiTickSystem;

    QList<std::shared_ptr<DrawSystem>> m_drawSystems;
    QList<std::shared_ptr<TickSystem>> m_tickSystems;

    QList<std::shared_ptr<GameObject>> m_toRemove;

};

#endif // GAMEWORLD_H
