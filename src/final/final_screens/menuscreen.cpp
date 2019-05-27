#include "menuscreen.h"

#include "view.h"
#include "engine/graphics/Graphics.h"
#include "engine/basics/gameworld.h"

#include "engine/UI/shapeui.h"
#include "engine/UI/textui.h"
#include "engine/UI/button.h"
#include "engine/UI/sliderui.h"
#include "engine/UI/uielement.h"
#include "engine/UI/uipanel.h"

#include "engine/components/uicomponent.h"
#include "engine/basics/input.h"
#include "engine/basics/application.h"
#include "engine/graphics/Camera.h"
#include "engine/basics/gameobject.h"
#include "engine/basics/gameworld.h"

#include "engine/systems/uidrawsystem.h"
#include "engine/systems/uiticksystem.h"

#include "engine/components/animationcomponent.h"
#include "engine/components/transformcomponent.h"
#include "engine/components/cameracomponent.h"

#include "final/final_screens/mainscreen.h"

MenuScreen::MenuScreen(View* view, Application* application)
    : GameScreen (view),
    m_application(application)
{
    std::shared_ptr<GameObject> uiObject = std::make_shared<GameObject>();
    std::shared_ptr<UIDrawSystem> uiDrawSystem = std::make_shared<UIDrawSystem>(m_camera);
    std::shared_ptr<UITickSystem> uiTickSystem = std::make_shared<UITickSystem>();
    std::shared_ptr<UIComponent> uiComponent = std::make_shared<UIComponent>();

    std::shared_ptr<UIPanel> messagePanel = std::make_shared<UIPanel>(1.f, 0.1f, 0.f, 0.f, glm::vec3(0.5f, 0.5f, 0.5f), "background");
    std::shared_ptr<TextUI> text = std::make_shared<TextUI>("Welcome!", 0.1f, glm::vec3(1.f), glm::vec3(0.35f, 0.8f, 0.f));
    std::shared_ptr<UIElement> uiText = std::dynamic_pointer_cast<UIElement>(text);
    messagePanel->addUIElement(0, "text", uiText);
    uiComponent->addPanel("messagePanel", messagePanel);

    std::shared_ptr<UIPanel> controlsPanel = std::make_shared<UIPanel>(0.3f, 0.9f, 0.7f, 0.1f, glm::vec3(0.1f, 0.5f, 0.5f), "controlPanel");
    std::shared_ptr<TextUI> awsdControls = std::make_shared<TextUI>("WASD to move", 0.05f, glm::vec3(1.f), glm::vec3(0.08f, 0.06f, 0.f));
    std::shared_ptr<UIElement> uiAWSD = std::dynamic_pointer_cast<UIElement>(awsdControls);
    controlsPanel->addUIElement(0, "awsd", uiAWSD);

    std::shared_ptr<TextUI> jumpControls = std::make_shared<TextUI>("Space to jump", 0.05f, glm::vec3(1.f), glm::vec3(0.08f, 0.12f, 0.f));
    std::shared_ptr<UIElement> uiJump = std::dynamic_pointer_cast<UIElement>(jumpControls);
    controlsPanel->addUIElement(1, "jump", uiJump);

    std::shared_ptr<TextUI> meditateControls = std::make_shared<TextUI>("1 to meditate", 0.05f, glm::vec3(1.f), glm::vec3(0.08f, 0.18f, 0.f));
    std::shared_ptr<UIElement> uiMed = std::dynamic_pointer_cast<UIElement>(meditateControls);
    controlsPanel->addUIElement(2, "meditate", uiMed);

    std::shared_ptr<TextUI> attackControls = std::make_shared<TextUI>("L click to attack", 0.05f, glm::vec3(1.f), glm::vec3(0.08f, 0.24f, 0.f));
    std::shared_ptr<UIElement> uiAttack = std::dynamic_pointer_cast<UIElement>(attackControls);
    controlsPanel->addUIElement(3, "attack", uiAttack);

    std::shared_ptr<TextUI> switchControls = std::make_shared<TextUI>("Q/E to switch", 0.05f, glm::vec3(1.f), glm::vec3(0.08f, 0.3f, 0.f));
    std::shared_ptr<UIElement> uiSwitch = std::dynamic_pointer_cast<UIElement>(switchControls);
    controlsPanel->addUIElement(4, "switch", uiSwitch);

    std::shared_ptr<TextUI> shiftControls = std::make_shared<TextUI>("Shift to sprint", 0.05f, glm::vec3(1.f), glm::vec3(0.08f, 0.36f, 0.f));
    std::shared_ptr<UIElement> uiShift = std::dynamic_pointer_cast<UIElement>(shiftControls);
    controlsPanel->addUIElement(5, "shift", uiShift);

    std::shared_ptr<Button> startButton = std::make_shared<Button>("Start", .5f, glm::vec3(0.5f), "button", "uiquad", glm::vec3(0.5f), glm::vec3(0.1f));
    std::function<void(Button&)> startCallBack = [this](Button&) mutable {
        std::shared_ptr<MainScreen> game = std::dynamic_pointer_cast<MainScreen>(this->m_application->getScreen("game"));
        game->setColor(m_playerColor);
        this->m_application->setScreen("game");
    };
    startButton->setCallback(startCallBack);
    std::shared_ptr<UIElement> uiStart = std::dynamic_pointer_cast<UIElement>(startButton);
    controlsPanel->addUIElement(6, "start", uiStart);
    uiComponent->addPanel("controlPanel", controlsPanel);

    std::shared_ptr<UIPanel> colorPanel = std::make_shared<UIPanel>(0.7f, 0.9f, 0.f, 0.1f);
    std::shared_ptr<SliderUI> slider = std::make_shared<SliderUI>(glm::vec3(0.7f, 0.7f, 0.7f), "slider", glm::vec3(0.05f), glm::vec3(0.5f, 0.02f, 1.f));
    std::function<void(SliderUI& slider)> sliderCallBack = [this](SliderUI& slider) mutable {
        float pointerPos = slider.getPointerPosition().x;
        float startPos = slider.getSliderStart();
        float endPos = slider.getSliderEnd();
        pointerPos -= startPos;
        pointerPos /= endPos;
        float r;
        float g;
        float b;
        if(pointerPos <= 0.5f){
            r = 1.f - pointerPos/0.5f;
            g = pointerPos/0.5f;
            b = 0.f;
        } else {
            pointerPos -= 0.5f;
            r = 0.f;
            g = 1.f - pointerPos/0.5f;;
            b = pointerPos/0.5f;
        }
        m_playerColor = glm::vec3(r, g, b);
        Material player;
        player.color = m_playerColor;
        player.shaderName = "skinning";
        m_graphics->addMaterial("player", player);
    };
    slider->setCallback(sliderCallBack);
    std::shared_ptr<UIElement> uiSlider = std::dynamic_pointer_cast<UIElement>(slider);
    colorPanel->addUIElement(0, "slider", uiSlider);
    uiComponent->addPanel("colorPanel", colorPanel);

    uiObject->addComponent<UIComponent>(uiComponent);
    m_gameWorld->addObject(uiObject);
    makePlayer();
    uiDrawSystem->addComponent(uiComponent, TypeID::value<UIComponent>());
    uiTickSystem->addComponent(uiComponent, TypeID::value<UIComponent>());
    m_gameWorld->addDrawSystem(uiDrawSystem);
    m_gameWorld->addTickSystem(uiTickSystem);
}

void MenuScreen::makePlayer(){
    m_gameWorld->addTickSystemType<AnimationComponent>();

    std::shared_ptr<GameObject> player = std::make_shared<GameObject>();
    std::string name("/course/cs195u/.archive/cur/student/gsymeshes/handozer.fbx");

    std::shared_ptr<AnimationComponent> animationPlayerComponent = std::make_shared<AnimationComponent>(name, glm::vec3(0, 1, 0), 180.f ,"player");
    animationPlayerComponent->add("idle1", 1.f, 100.f, 50.f, 0.f);
    animationPlayerComponent->changeCurrentAnimation("idle1");
    animationPlayerComponent->setDrawScale(.003f);

    std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>();
    transformComponent->setPosition(glm::vec3(0.3, 0.7, 0.9));

    std::shared_ptr<CameraComponent> cameraComponent = std::make_shared<CameraComponent>(m_camera, m_view);

    player->addComponent<TransformComponent>(transformComponent);
    player->addComponent<CameraComponent>(cameraComponent);
    player->addComponent<AnimationComponent>(animationPlayerComponent);

    m_gameWorld->addObject(player);
}

void MenuScreen::initializeGL(){
    Material player;
    player.color = m_playerColor;
    player.shaderName = "skinning";
    m_graphics->addMaterial("player", player);
}

void MenuScreen::onSwitch(){
    getView()->setCaptureMouse(false);
}

void MenuScreen::keyPressEvent(QKeyEvent *event) {

}
