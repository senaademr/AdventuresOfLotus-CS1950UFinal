#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "engine/util/CommonIncludes.h"

#include <QList>

#include "engine/components/component.h"
#include "engine/util/util.h"
#include "engine/basics/typeid.h"
#include <QMap>

class TransformComponent;

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
    GameObject();
    template <class T>
    void addComponent(std::shared_ptr<Component> component){
        if(hasComponent<T>()){
//            std::cout << "Warning: replacing a component" << std::endl;
        }
        component->setGameObject(shared_from_this());
        m_components.insert(TypeID::value<T>(), component);
    }

    template <class T>
    void removeComponent(std::shared_ptr<Component> component){
        if(!hasComponent<T>()){
            std::cout << "trying to remove a component that is not in" << std::endl;
            return;
        }
        m_components.remove(TypeID::value<T>());

    }

    template <class T>
    std::shared_ptr<T> getComponent(){
        if(!hasComponent<T>()){
            std::cout << "no component of the requested type: " << TypeID::value<T>() << std::endl;
            throw -1;
        }
        std::shared_ptr<Component> component = m_components.value(TypeID::value<T>());
        return std::dynamic_pointer_cast<T>(component);
    }


    template <class T>
    bool hasComponent(){
        return m_components.contains(TypeID::value<T>());
    }

    std::shared_ptr<Component> getComponent(size_t id);
    bool hasComponent(size_t id);

    QList<size_t> getKeys();

private:
    //QMap<ComponentType, std::shared_ptr<Component>> m_components;
    QMap<size_t, std::shared_ptr<Component> > m_components;
};

#endif // GAMEOBJECT_H
