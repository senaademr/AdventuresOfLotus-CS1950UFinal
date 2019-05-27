#include "cameracomponent.h"

#include "engine/basics/input.h"
#include "engine/components/transformcomponent.h"
#include "engine/basics/gameobject.h"
#include "engine/graphics/Camera.h"
#include "view.h"

CameraComponent::CameraComponent(std::shared_ptr<Camera> camera, View* view)
    : Component(),
      Tickable(),
      m_input(Input::getGlobalInstance()),
      m_camera(camera),
      m_view(view),
      m_isThirdPerson(true),
      m_thirdPersonDistance(5.f),
      m_cameraSpeed(200.f)

{

}


void CameraComponent::tick(float seconds){
    std::shared_ptr<GameObject> gameObject = this->getGameObject();
    std::shared_ptr<TransformComponent> transformComponent =
            gameObject->getComponent<TransformComponent>();
    assert(transformComponent != nullptr);
    m_camera->setEye(transformComponent->getPosition());

    //m_camera->translate(glm::vec3(0, transformComponent->getSize().y, 0));
    m_camera->translate(glm::vec3(0, 2.5, 0));

    if(m_input->getWheelDelta() > 0 && m_isThirdPerson){
        m_thirdPersonDistance /= 1.2f;
    }
    else if(m_input->getWheelDelta() < 0 && m_isThirdPerson){
        m_thirdPersonDistance *= 1.2f;

    }
//    if(m_input->isKeyJustPressed(Qt::Key_T)){
//        m_isThirdPerson = !m_isThirdPerson;
//    }

    glm::vec2 mouseDelta = m_input->getMouseDelta();
    int deltaX = static_cast<int>(mouseDelta.x);
    int deltaY = static_cast<int>(mouseDelta.y);

    m_camera->rotate(-deltaX / m_cameraSpeed, -deltaY / m_cameraSpeed);
    if(m_isThirdPerson){
        glm::vec3 lookVector = glm::normalize(m_camera->getLook());
        m_camera->translate(- lookVector * m_thirdPersonDistance);
    }
}

glm::vec3 CameraComponent::getCameraDirection(){
    return m_camera->getLook();

}
