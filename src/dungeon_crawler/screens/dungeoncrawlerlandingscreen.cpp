#include "dungeoncrawlerlandingscreen.h"

#include "view.h"
#include "engine/graphics/Graphics.h"
#include "engine/basics/gameworld.h"

#include "engine/components/uicomponent.h"
#include "engine/basics/input.h"
#include "engine/basics/application.h"
#include "engine/graphics/Camera.h"
#include "engine/basics/gameobject.h"
#include "engine/basics/gameworld.h"

#include "engine/UI/shapeui.h"
#include "engine/UI/textui.h"

#include "engine/components/objectdrawcomponent.h"
#include "engine/basics/gameobject.h"
#include "engine/components/transformcomponent.h"
#include "engine/components/cameracomponent.h"
#include "engine/components/physicscomponent.h"

#include "engine/components/pausecomponent.h"


DungeonCrawlerLandingScreen::DungeonCrawlerLandingScreen(View* view, Application* application)
    : GameScreen (view),
    m_application(application)
{
//    glm::vec3 position = glm::vec3(0.3, 0.7, 0.f);
//    std::shared_ptr<ShapeUI> shape = std::make_shared<ShapeUI>(glm::vec3(0.4, 0.1, 1.f), "green", "uiquad", position, glm::vec3(0.4, 0.1, 1.f));
//    glm::vec3 textposition = glm::vec3(0.4, 0.72, 0.f);
//    std::shared_ptr<TextUI> text = std::make_shared<TextUI>("Hello!",  0.1, glm::vec3(0.f), textposition);
//    text->setAlignment(TextAlignment::CENTER_CENTER);



//    std::shared_ptr<GameObject> pauseObject = std::make_shared<GameObject>();
//    std::shared_ptr<UIComponent> pauseMessageComp = std::make_shared<UIComponent>(position);
//    pauseMessageComp->addElement(shape, 1);
//    pauseMessageComp->addElement(text, 2);

//    pauseObject->addComponent<UIComponent>(pauseMessageComp);
//    m_gameWorld->addObject(pauseObject);

    m_gameWorld->addTickSystemType<CameraComponent>();
    m_gameWorld->addTickSystemType<PhysicsComponent>();
    m_gameWorld->addTickSystemType<PauseComponent>();

    m_gameWorld->addObject(PauseComponent::getPauseObject(getView()));

    makePlayer();

    //m_gameWorld->removeObject(pauseObject);

}

void DungeonCrawlerLandingScreen::initializeGL(){
    Material red;
    red.color = glm::vec3(1, 0, 0);
    m_graphics->addMaterial("red", red);
}

void DungeonCrawlerLandingScreen::onSwitch(){
    getView()->setCaptureMouse(false);
}

void DungeonCrawlerLandingScreen::makePlayer(){
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>();
    std::shared_ptr<ObjectDrawComponent> drawPlayerComponent = std::make_shared<ObjectDrawComponent>();
    drawPlayerComponent->setShapeType("cylinder");
    std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>();
    transformComponent->setSize(glm::vec3(1));
    transformComponent->setPosition(glm::vec3(0));
    //transformComponent->setPosition(glm::vec3(, 1, 5));

    //std::shared_ptr<DCPlayerInputComponent> playerInputComponent = std::make_shared<DCPlayerInputComponent>(player, getGameWorld(), m_camera);
    std::shared_ptr<CameraComponent> cameraComponent = std::make_shared<CameraComponent>(m_camera, m_view);
    std::shared_ptr<PhysicsComponent> physicsComponent = std::make_shared<PhysicsComponent>();
    physicsComponent->setGravity(false);
//    std::shared_ptr<CollisionComponent> collisionComponent
//            = std::make_shared<CollisionComponent>(player, transformComponent, ColliderType::CYLINDER);
//    collisionComponent->setResponse(std::make_shared<PlayerCollisionResponseComponent>(player, m_healthUI));
//    std::shared_ptr<RaycastComponent> rayCastComponent = std::make_shared<RaycastComponent>(player, m_collisionSystem);
//    std::shared_ptr<HealthComponent> healthComponent = std::make_shared<HealthComponent>(player, PLAYER_STARTING_HEALTH);

    player->addComponent<TransformComponent>(transformComponent);
    //player->addComponent(playerInputComponent);
    player->addComponent<CameraComponent>(cameraComponent);
    player->addComponent<PhysicsComponent>(physicsComponent);
    player->addComponent<ObjectDrawComponent>(drawPlayerComponent);
    //player->addComponent(collisionComponent);
    //player->addComponent(rayCastComponent);
    //player->addComponent(healthComponent);
    m_gameWorld->addObject(player);
}

//void DungeonCrawlerLandingScreen::mousePressEvent(QMouseEvent *event)
//{
//    m_application->setScreen(std::make_shared<DungeonCrawlerScreen>(m_view));
//}
