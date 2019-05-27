#include "pausecomponent.h"

#include "engine/basics/input.h"
#include "engine/basics/gameobject.h"
#include "engine/screens/pausescreen.h"
#include "engine/basics/application.h"
#include "view.h"


PauseComponent::PauseComponent(View *view)
    : Component(),
      m_view(view),
      m_input(nullptr)
{
    m_input = Input::getGlobalInstance();
}


std::shared_ptr<GameObject> PauseComponent::getPauseObject(View* view){
    std::shared_ptr<GameObject> pauseObject = std::make_shared<GameObject>();
    std::shared_ptr<PauseComponent> pauseComp = std::make_shared<PauseComponent>(view);
    pauseObject->addComponent<PauseComponent>(pauseComp);
    return pauseObject;
}

void PauseComponent::tick(float seconds){
    if(m_input->isKeyJustPressed(Qt::Key_P)){
        std::cout << "pausing" << std::endl;
        std::shared_ptr<Application> application =  m_view->getApplication();
        std::shared_ptr<Screen> pauseScreen = std::make_shared<PauseScreen>(m_view, application.get());
//        application->pushScreen(pauseScreen);
    }
}
