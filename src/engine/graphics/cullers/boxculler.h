#ifndef BOXCULLER_H
#define BOXCULLER_H

#include "culler.h"
#include <QList>

class TransformComponent;


class BoxCuller : public Culler
{
public:
    BoxCuller(std::shared_ptr<TransformComponent> transform);

    static const QList<glm::vec3>& getMultipliers(){
        static QList<glm::vec3> mulipliers = {glm::vec3(.5f, .5f, .5f),
                                                   glm::vec3(.5f, .5f, -.5f),
                                                   glm::vec3(.5f, -.5f, .5f),
                                                   glm::vec3(.5f, -.5f, -.5f),
                                                   glm::vec3(-.5f, .5f, .5f),
                                                   glm::vec3(-.5f, .5f, -.5f),
                                                   glm::vec3(-.5f, -.5f, .5f),
                                                   glm::vec3(-.5f, -.5f, -.5f)};
        return mulipliers;
    }

    // Culler interface
public:
    bool shouldCull(QList<glm::vec4> &planes) override;
private:

    QList<glm::vec4> getCorners();
    //bool cullPlane(glm::vec4 &plane, QList<glm::vec4> &corners);


};

#endif // BOXCULLER_H
