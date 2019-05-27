#ifndef COMPONENT_H
#define COMPONENT_H

#include "engine/util/CommonIncludes.h"

class GameObject;

class Component
{
public:
    Component();
    virtual ~Component();

    std::shared_ptr<GameObject> getGameObject();
    void setGameObject(std::shared_ptr<GameObject> gameObject);

protected:
    std::shared_ptr<GameObject> m_gameObject;
};

#endif // COMPONENT_H
