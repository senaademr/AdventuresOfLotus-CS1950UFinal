#include "deathcomponent.h"

#include "final/final_screens/finalapplication.h"

DeathComponent::DeathComponent(Application* app):
    m_application(app)
{
}

void DeathComponent::callGameOver(){
    m_application->setScreen("gameOver");
}
