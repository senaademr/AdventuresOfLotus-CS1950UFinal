#include "pausescreen.h"

#include "engine/basics/application.h"
#include "engine/components/unpausecomponent.h"
#include "engine/basics/gameobject.h"
#include "engine/basics/gameworld.h"
#include "engine/UI/textui.h"
#include "engine/UI/shapeui.h"
#include "view.h"
#include "engine/components/uicomponent.h"
#include "engine/UI/textalignment.h"
#include "engine/UI/button.h"

PauseScreen::PauseScreen(View *view, Application *application)
    : GameScreen(view),
      m_application(application)
{
    std::shared_ptr<GameWorld> gameWorld = getGameWorld();
    //gameWorld->addTickSystemType<(ComponentType::PAUSE);

    std::shared_ptr<GameObject> unPauseObject = std::make_shared<GameObject>();
    std::shared_ptr<UnpauseComponent> unpauseComp = std::make_shared<UnpauseComponent>(this);
    //unPauseObject->addComponent(unpauseComp);
    gameWorld->addObject(unPauseObject);


//    std::shared_ptr<UIInfo> info= std::make_shared<UIInfo>(glm::vec2(100.f, 350.f));
//    TextInfo text = TextInfo("Press p to unpause", 80, glm::vec3(1));
//    text.relativeLocation = glm::vec2(20, 20);
//    ShapeInfo shape = ShapeInfo(glm::vec2(0), true, glm::vec2(600, 100), "red");
//    info->setText(text);
//    info->setShape(shape);
    auto callback = [this](){
        this->unpause();
    };
//    std::shared_ptr<Button> button = std::make_shared<Button>(glm::vec2(600, 100), callback);

//    std::shared_ptr<ShapeUI> shape = std::make_shared<ShapeUI>(glm::vec2(600, 100), "green");
//    std::shared_ptr<TextUI> text = std::make_shared<TextUI>("Click to unpause!", 80, glm::vec3(1), shape->getTransform());
//    text->setAlignment(TextAlignment::CENTER_CENTER);

//    glm::vec2 position = glm::vec2(100.f, 400.f);

//    std::shared_ptr<GameObject> pauseObject = std::make_shared<GameObject>();
//    std::shared_ptr<UIComponent> pauseMessageComp = std::make_shared<UIComponent>(position);
//    pauseMessageComp->addElement(shape, 1);
//    pauseMessageComp->addElement(text, 2);
//    pauseMessageComp->addButton(button);

//    pauseObject->addComponent<UIComponent>(pauseMessageComp);
//    gameWorld->addObject(pauseObject);
}


void PauseScreen::initializeGL(){

}

void PauseScreen::onSwitch(){
    getView()->setCaptureMouse(false);
}

void PauseScreen::unpause(){
//    m_application->popScreen();
}

