#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "engine/components/tickable.h"
#include "engine/components/component.h"

class Input;
class Camera;
class View;

class CameraComponent : public Component, public Tickable
{
public:
    CameraComponent (std::shared_ptr<Camera> camera, View* view);

    void tick(float seconds);
    glm::vec3 getCameraDirection();

private:
    std::shared_ptr<Input> m_input;
    std::shared_ptr<Camera> m_camera;
    View* m_view;
    bool m_isThirdPerson;
    float m_thirdPersonDistance;
    float m_cameraSpeed;
};


#endif // CAMERACOMPONENT_H
