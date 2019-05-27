#include "unpausecomponent.h"

#include "engine/basics/input.h"
#include "engine/screens/pausescreen.h"

UnpauseComponent::UnpauseComponent(PauseScreen *pauseScreen)
    : Component(),
      m_pauseScreen(pauseScreen),
      m_input(nullptr)
{
    m_input = Input::getGlobalInstance();
}


void UnpauseComponent::tick(float seconds){
    if(m_input->isKeyJustPressed(Qt::Key_P)){
        assert(m_pauseScreen);
        m_pauseScreen->unpause();
    }
}
