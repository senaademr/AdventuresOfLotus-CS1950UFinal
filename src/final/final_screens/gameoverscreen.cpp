#include "gameoverscreen.h"

#include "engine/basics/gameobject.h"
#include "engine/basics/gameworld.h"
#include "view.h"
#include "finalapplication.h"
#include "engine/components/uicomponent.h"
#include "engine/systems/uidrawsystem.h"
#include "engine/systems/uiticksystem.h"

#include "mainscreen.h"
#include "menuscreen.h"

#include "engine/UI/shapeui.h"
#include "engine/UI/textui.h"
#include "engine/UI/button.h"
#include "engine/UI/sliderui.h"
#include "engine/UI/uielement.h"
#include "engine/UI/uipanel.h"

GameOverScreen::GameOverScreen(View *view, Application *application)
    :GameScreen(view),
      m_application(application)
{
    std::shared_ptr<GameObject> uiObject = std::make_shared<GameObject>();
    std::shared_ptr<UIDrawSystem> uiDrawSystem = std::make_shared<UIDrawSystem>(m_camera);
    std::shared_ptr<UITickSystem> uiTickSystem = std::make_shared<UITickSystem>();
    std::shared_ptr<UIComponent> uiComponent = std::make_shared<UIComponent>();

    std::shared_ptr<UIPanel> messagePanel = std::make_shared<UIPanel>(1.f, 0.4f, 0.f, 0.f, glm::vec3(0.5f, 0.5f, 0.5f), "background");
    std::shared_ptr<TextUI> text = std::make_shared<TextUI>("GameOver!", 0.1f, glm::vec3(1.f), glm::vec3(0.35f, 0.8f, 0.f));
    std::shared_ptr<UIElement> uiText = std::dynamic_pointer_cast<UIElement>(text);
    messagePanel->addUIElement(0, "text", uiText);
    uiComponent->addPanel("messagePanel", messagePanel);

    std::shared_ptr<UIPanel> controlsPanel = std::make_shared<UIPanel>(1.f, 0.6f, 0.f, 0.4f, glm::vec3(0.1f, 0.5f, 0.5f), "controlPanel");
    std::shared_ptr<Button> startButton = std::make_shared<Button>("Start", .5f, glm::vec3(0.5f), "button", "uiquad", glm::vec3(0.5f), glm::vec3(0.1f));
    std::function<void(Button&)> startCallBack = [this](Button&) mutable {
        this->m_application->removeScreen("game");
        std::shared_ptr<MainScreen> game = std::make_shared<MainScreen>(m_view, m_application);
        this->m_application->addScreen("game", game);
//        game->setColor(m_playerColor);
        this->m_application->setScreen("game");
    };
    startButton->setCallback(startCallBack);
    std::shared_ptr<UIElement> uiStart = std::dynamic_pointer_cast<UIElement>(startButton);
    controlsPanel->addUIElement(0, "start", uiStart);
    uiComponent->addPanel("controlPanel", controlsPanel);

    uiObject->addComponent<UIComponent>(uiComponent);
    m_gameWorld->addObject(uiObject);
    uiDrawSystem->addComponent(uiComponent, TypeID::value<UIComponent>());
    uiTickSystem->addComponent(uiComponent, TypeID::value<UIComponent>());
    m_gameWorld->addDrawSystem(uiDrawSystem);
    m_gameWorld->addTickSystem(uiTickSystem);
}

void GameOverScreen::initializeGL(){

}

void GameOverScreen::onSwitch(){
    getView()->setCaptureMouse(false);
}

void GameOverScreen::keyPressEvent(QKeyEvent *event){

}
