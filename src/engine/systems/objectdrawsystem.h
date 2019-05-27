#ifndef OBJECTDRAWSYSTEM_H
#define OBJECTDRAWSYSTEM_H

#include "drawsystem.h"

class ObjectDrawSystem : public DrawSystem
{
public:
    ObjectDrawSystem(std::shared_ptr<Camera> camera);

    // DrawSystem interface
public:
    void draw() override;

private:

    QList<glm::vec4> calculateCullInfo();
};

#endif // OBJECTDRAWSYSTEM_H
