#ifndef CULLER_H
#define CULLER_H


#include "engine/util/CommonIncludes.h"
#include <QList>

class TransformComponent;

class Culler
{
public:
    Culler(std::shared_ptr<TransformComponent> transform);

    virtual bool shouldCull(QList<glm::vec4> &planes) = 0;

protected:
    std::shared_ptr<TransformComponent> m_transform;
};

#endif // CULLER_H
