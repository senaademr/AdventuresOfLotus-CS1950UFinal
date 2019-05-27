#ifndef SYSTEM_H
#define SYSTEM_H

#include <QList>

#include "engine/components/component.h"
#include "engine/util/CommonIncludes.h"
#include "engine/basics/typeid.h"


class System
{
public:
    System(size_t componentTypeID);
    System();

    void addType(size_t componentTypeID);

//    template <class T>
//    void addComponent(std::shared_ptr<Component> component){
//        if(hasComponentType(TypeID::value<T>()) ){
//            m_components.append(component);
//        }
//        else{
//            std::cout << "Trying to add bad component" << std::endl;
//            throw -1;
//        }
//    }
    void addComponent(std::shared_ptr<Component> component, size_t componentTypeID);
    void removeComponent(std::shared_ptr<Component> component);

    QList<std::shared_ptr<Component>> getComponents();
    bool hasComponentTypeID(size_t componentTypeID);

protected:
    QList<std::shared_ptr<Component>> m_components;
    QList<size_t> m_componentTypeIDs;

};

#endif // SYSTEM_H
