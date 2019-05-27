#ifndef DRAWSYSTEM_H
#define DRAWSYSTEM_H

#include "engine/systems/system.h"

class Graphics;
class Drawable;
class Camera;

class DrawSystem : public System
{
public:
    DrawSystem(std::shared_ptr<Camera> camera, size_t componentTypeID);
    virtual ~DrawSystem();

    virtual void draw() = 0;

protected:
    Graphics* m_graphics;
    std::shared_ptr<Camera> m_camera;

private:
    QList<glm::vec4> calculateCullInfo();
};

#endif // DRAWSYSTEM_H
