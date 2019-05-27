#include "mainscreen.h"


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
#include "engine/systems/collisionsystem.h"
#include "engine/systems/camerasystem.h"
#include "engine/systems/uidrawsystem.h"
#include "engine/systems/uiticksystem.h"
#include "engine/components/pausecomponent.h"
#include "engine/components/collisioncomponent.h"
#include "engine/components/collisionresponsecomponent.h"
#include "engine/components/continuouscollisioncomponent.h"
#include "engine/components/uicomponent.h"
#include "engine/components/timeremovecomponent.h"
#include "engine/components/aicomponent.h"

#include "engine/systems/continuouscollisionsystem.h"

#include "final/final_components/collision_components/spherecollisioncomponent.h"
#include "final/final_components/collision_components/cylindercollisioncomponent.h"
#include "final/final_components/player_components/playercollisionresponsecomponent.h"
#include "final/final_components/player_components/playerabilitycomponent.h"
#include "final/final_components/player_components/playerlevelcomponent.h"
#include "final/final_components/terrain_components/terrainsettingcomponent.h"
#include "final/final_components/enemy_components/enemymovecomponent.h"
#include "final/final_components/player_components/deathcomponent.h"
#include "final/final_components/player_components/dynamicmovecomponent.h"

#include "final/enemygeneration/enemyremovalsystem.h"

#include "engine/components/animationcomponent.h"

#include "engine/UI/uipanel.h"

#include "final/mapgeneration/trianglemeshterraingenerator.h"

#include "final/final_components/player_components/playercontrolcomponent.h"
#include "final/mapgeneration/chunkloadingsystem.h"

#include "engine/graphics/Texture2D.h"


MainScreen::MainScreen(View *view, Application *application)
    : GameScreen(view),
      m_application(application)
{
    m_application->removeScreen("menu");
    m_gameWorld->addTickSystemType<PlayerAbilityComponent>();
    m_gameWorld->addTickSystemType<PhysicsComponent>();
    m_gameWorld->addTickSystemType<DynamicMoveComponent>();
    m_gameWorld->addTickSystemType<PauseComponent>();
    m_gameWorld->addTickSystemType<PlayerControlComponent>();
    m_gameWorld->addTickSystemType<TerrainSettingComponent>();
    //m_gameWorld->addTickSystemType<EnemyMoveComponent>();
    m_gameWorld->addTickSystemType<AnimationComponent>();
    m_gameWorld->addTickSystemType<TimeRemoveComponent>();
    m_gameWorld->addTickSystemType<AIComponent>();

    m_gameWorld->addObject(PauseComponent::getPauseObject(getView()));

    std::shared_ptr<GameObject> player = makePlayer();
    makeUI(player);
    auto playerTransformComponent = player->getComponent<TransformComponent>();
    auto playerLevelComponent = player->getComponent<PlayerLevelComponent>();

    std::shared_ptr<EnemyRemovalSystem> enemyRemoval = std::make_shared<EnemyRemovalSystem>( m_gameWorld, playerLevelComponent);
    m_gameWorld->addTickSystem(enemyRemoval);

    std::shared_ptr<ChunkLoadingSystem> chunkLoadingSystem = std::make_shared<ChunkLoadingSystem>(m_gameWorld, enemyRemoval, playerTransformComponent);
    m_gameWorld->addTickSystem(chunkLoadingSystem);



    std::shared_ptr<ContinuousCollisionSystem> continuousCollisionSystem
            = std::make_shared<ContinuousCollisionSystem>(chunkLoadingSystem);
    m_gameWorld->addTickSystem(continuousCollisionSystem);
    std::shared_ptr<CollisionSystem> collisionSystem = std::make_shared<CollisionSystem>(m_camera, continuousCollisionSystem);
    m_gameWorld->addTickSystem(collisionSystem);

    m_gameWorld->addTickSystem(std::make_shared<CameraSystem>());   //make sure camera system is the last system you add
}

void MainScreen::initializeGL(){
    m_graphics->addTexture("grass", ":/images/grass.png");
    m_graphics->addTexture("ice", ":/images/ice.png");
    m_graphics->addTexture("rocky", ":/images/rocky.png");

    m_graphics->addTexture("minecraftRock", ":/images/minecraftRock.png");
    m_graphics->getTexture("minecraftRock")->setFilterMethod(Texture::FILTER_METHOD::NEAREST);

    m_graphics->addTexture("minecraftSand", ":/images/minecraftSand.png");
    m_graphics->getTexture("minecraftSand")->setFilterMethod(Texture::FILTER_METHOD::NEAREST);

    m_graphics->addTexture("terrain", ":/images/terrain.png");
    m_graphics->getTexture("terrain")->setFilterMethod(Texture::FILTER_METHOD::NEAREST);

    m_graphics->addTexture("rightpunch", ":/images/screenpunch1.png");
    m_graphics->addTexture("leftpunch", ":/images/screenpunch2.png");
    m_graphics->addTexture("stomp", ":/images/screenstomp.png");

    Material green;
    green.color = glm::vec3(0, 1, 0);
    m_graphics->addMaterial("green", green);

    Material red;
    red.color = glm::vec3(1, 0, 0);
    m_graphics->addMaterial("red", red);

    Material redTransparent;
    redTransparent.color = glm::vec3(1, 0, 0);
    redTransparent.alpha = .3;
    m_graphics->addMaterial("redTransparent", redTransparent);

    Material grass;
    grass.textureName = "grass";
    m_graphics->addMaterial("grass", grass);

    Material ice;
    ice.textureName = "ice";
    ice.textureRepeat = glm::vec2(.2);
    m_graphics->addMaterial("ice", ice);

    Material rocky;
    rocky.textureName = "rocky";
    rocky.textureRepeat = glm::vec2(1);
    m_graphics->addMaterial("rocky", rocky);

    Material minecraftSand;
    minecraftSand.textureName = "minecraftSand";
    minecraftSand.textureRepeat = glm::vec2(1);
    m_graphics->addMaterial("minecraftSand", minecraftSand);

    Material minecraftRock;
    minecraftRock.textureName = "minecraftRock";
    m_graphics->addMaterial("minecraftRock", minecraftRock);

    Material terrain;
    terrain.textureName = "terrain";
    m_graphics->addMaterial("terrain", terrain);

    Material playerMaterial;
    playerMaterial.color = m_playerColor;
    playerMaterial.shaderName = "skinning";
    m_graphics->addMaterial("player", playerMaterial);

    Material attackMaterial;
    attackMaterial.color = m_playerColor;
    m_graphics->addMaterial("attack", attackMaterial);

    Material magmaAquaticMaterial;
    magmaAquaticMaterial.color = glm::vec3(0.38f, 0.92f, 0.84f);
    magmaAquaticMaterial.shaderName = "skinning";
    m_graphics->addMaterial("magmaAquatic", magmaAquaticMaterial);

    Material magmaDesertMaterial;
    magmaDesertMaterial.color = glm::vec3(0.72f, 0.72f, 0.47f);
    magmaDesertMaterial.shaderName = "skinning";
    m_graphics->addMaterial("magmaDesert", magmaDesertMaterial);

    Material spaceMountainMaterial;
    spaceMountainMaterial.color = glm::vec3(0.73f, 0.84f, 0.87f);
    spaceMountainMaterial.shaderName = "skinning";
    m_graphics->addMaterial("spaceMountain", spaceMountainMaterial);

    Material spaceAquaticMaterial;
    spaceAquaticMaterial.color = glm::vec3(0.38f, 0.60f, 0.92f);
    spaceAquaticMaterial.shaderName = "skinning";
    m_graphics->addMaterial("spaceAquatic", spaceAquaticMaterial);

    Material spiderMountainMaterial;
    spiderMountainMaterial.color = glm::vec3(0.66f, 0.76f, 0.67f);
    spiderMountainMaterial.shaderName = "skinning";
    m_graphics->addMaterial("spiderMountain", spiderMountainMaterial);

    Material spiderDesertMaterial;
    spiderDesertMaterial.color = glm::vec3(0.9f, 0.65f, 0.35f);
    spiderDesertMaterial.shaderName = "skinning";
    m_graphics->addMaterial("spiderDesert", spiderDesertMaterial);
}

void MainScreen::onSwitch(){
    getView()->setCaptureMouse(true);
}

void MainScreen::makeCylinder(){
    std::shared_ptr<GameObject> cylinder = std::make_shared<GameObject>();
    std::shared_ptr<ObjectDrawComponent> drawPlayerComponent = std::make_shared<ObjectDrawComponent>();
    drawPlayerComponent->setShapeType("cylinder");
    std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>();
    transformComponent->setSize(glm::vec3(1, 1, 1));
    transformComponent->setPosition(glm::vec3(2, 22, 2));

    std::shared_ptr<PhysicsComponent> physicsComponent = std::make_shared<PhysicsComponent>();
    physicsComponent->setGravity(true);
    std::shared_ptr<CollisionComponent> collisionComponent = std::make_shared<CylinderCollisionComponent>();
    std::shared_ptr<CollisionResponseComponent> collisionResponseComponent = std::make_shared<CollisionResponseComponent>(""); // general response
    std::shared_ptr<ContinuousCollisionComponent> continousComponent = std::make_shared<ContinuousCollisionComponent>(transformComponent);

    cylinder->addComponent<TransformComponent>(transformComponent);
    cylinder->addComponent<PhysicsComponent>(physicsComponent);
    cylinder->addComponent<ObjectDrawComponent>(drawPlayerComponent);
    cylinder->addComponent<CollisionComponent>(collisionComponent);
    cylinder->addComponent<CollisionResponseComponent>(collisionResponseComponent);
    cylinder->addComponent<ContinuousCollisionComponent>(continousComponent);
    m_gameWorld->addObject(cylinder);
}

void MainScreen::makeSphere(){
    std::shared_ptr<GameObject> sphere = std::make_shared<GameObject>();
    std::shared_ptr<ObjectDrawComponent> drawPlayerComponent = std::make_shared<ObjectDrawComponent>();
    drawPlayerComponent->setShapeType("sphere");
    std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>();
    transformComponent->setSize(glm::vec3(1));
    transformComponent->setPosition(glm::vec3(0));

    std::shared_ptr<PhysicsComponent> physicsComponent = std::make_shared<PhysicsComponent>();
    physicsComponent->setGravity(false);
    std::shared_ptr<CollisionComponent> collisionComponent = std::make_shared<SphereCollisionComponent>();
    std::shared_ptr<CollisionResponseComponent> collisionResponseComponent = std::make_shared<CollisionResponseComponent>(""); // general response

    sphere->addComponent<TransformComponent>(transformComponent);
    sphere->addComponent<PhysicsComponent>(physicsComponent);
    sphere->addComponent<ObjectDrawComponent>(drawPlayerComponent);
    sphere->addComponent<CollisionComponent>(collisionComponent);
    sphere->addComponent<CollisionResponseComponent>(collisionResponseComponent);
    m_gameWorld->addObject(sphere);
}


std::shared_ptr<GameObject> MainScreen::makePlayer(){
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>();
    std::shared_ptr<PlayerAbilityComponent> playerAbility = std::make_shared<PlayerAbilityComponent>();
    playerAbility->addAttack("leftpunch");
    playerAbility->addAttack("rightpunch");
    playerAbility->addAttack("stomp");
    std::string name("/course/cs195u/.archive/cur/student/gsymeshes/handozer.fbx");
    std::shared_ptr<AnimationComponent> animationPlayerComponent = std::make_shared<AnimationComponent>(name, "player");
    makePlayerAnimations(animationPlayerComponent);
    animationPlayerComponent->changeCurrentAnimation("idle1");
    animationPlayerComponent->setDrawScale(glm::vec3(.01));

    std::shared_ptr<DeathComponent> deathComponent = std::make_shared<DeathComponent>(m_application);
    player->addComponent<DeathComponent>(deathComponent);

    std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>();
    transformComponent->setPosition(glm::vec3(0, 10 , 0));
    glm::vec3 size = glm::vec3(0.8, 2, 0.8);
    //glm::vec3 size = glm::vec3(1);
    transformComponent->setSize(size);

//    std::shared_ptr<ObjectDrawComponent> objectDraw = std::make_shared<ObjectDrawComponent>();
//    objectDraw->setMaterial("redTransparent");

//    std::shared_ptr<ObjectDrawComponent> continuousCollisionElipsoidDraw = std::make_shared<ObjectDrawComponent>();
//    continuousCollisionElipsoidDraw->setMaterial("redTransparent");

    std::shared_ptr<CameraComponent> cameraComponent = std::make_shared<CameraComponent>(m_camera, m_view);
    std::shared_ptr<PhysicsComponent> physicsComponent = std::make_shared<PhysicsComponent>();
    physicsComponent->setGravity(true);
    std::shared_ptr<CollisionComponent> collisionComponent = std::make_shared<CylinderCollisionComponent>();
    std::shared_ptr<Component> collisionResponseComponent = std::make_shared<PlayerCollisionResponseComponent>();
    // ContinuousCollisionComponent is created after transform because it requires transform component
    std::shared_ptr<ContinuousCollisionComponent> continousComponent = std::make_shared<ContinuousCollisionComponent>(transformComponent);
    std::shared_ptr<DynamicMoveComponent> dynamicMove = std::make_shared<DynamicMoveComponent>(20.f, 100.f, 0.f);
    std::shared_ptr<PlayerControlComponent> playerControl = std::make_shared<PlayerControlComponent>(m_camera, m_gameWorld);
    std::shared_ptr<TerrainSettingComponent> terrainSetting = std::make_shared<TerrainSettingComponent>();
    std::shared_ptr<PlayerLevelComponent> playerLevel = std::make_shared<PlayerLevelComponent>();

    //std::shared_ptr<TerrainSettingComponent> terrainSetting = std::make_shared<TerrainSettingComponent>();

//    player->addComponent<ObjectDrawComponent>(objectDraw);
    //player->addComponent<ObjectDrawComponent>(continuousCollisionElipsoidDraw);
    player->addComponent<DynamicMoveComponent>(dynamicMove);
    player->addComponent<TransformComponent>(transformComponent);
    player->addComponent<CameraComponent>(cameraComponent);
    player->addComponent<PhysicsComponent>(physicsComponent);
    player->addComponent<AnimationComponent>(animationPlayerComponent);
    player->addComponent<CollisionComponent>(collisionComponent);
    player->addComponent<CollisionResponseComponent>(collisionResponseComponent);
    player->addComponent<PlayerControlComponent>(playerControl);
    player->addComponent<PlayerLevelComponent>(playerLevel);
    player->addComponent<PlayerAbilityComponent>(playerAbility);
    player->addComponent<ContinuousCollisionComponent>(continousComponent);
    player->addComponent<TerrainSettingComponent>(terrainSetting);
    playerAbility->updateAttackAnimations();
    playerControl->updateAttackTimer();
    m_gameWorld->addObject(player);
    return player;
}

//float MainScreen::getAttackFrameSpeed(float attackSpeed, float numberOfFrames){
//    float fps = 60.f;
//    return attackSpeed * fps /numberOfFrames;
//}

void MainScreen::makePlayerAnimations(std::shared_ptr<AnimationComponent> &playerAnim){


    playerAnim->add("walk", 2.f, 20.f, 10.f, 0.f);
    playerAnim->add("backwardWalk", 2.f, -20.f, 10, 0.f);
    playerAnim->add("idle1", 1.f, 100.f, 50.f, 0.f);
    playerAnim->add("jump", 1.f, 14.f, 200.f, 1.f);
    playerAnim->add("freefall", 1.f, 40.f, 230.f, 0.f);
    playerAnim->add("idle2", 1.f, 100.f, 290.f, 0.f);
    playerAnim->add("sneakwalk", 1.f, 70.f, 400.f, 0.f);
    playerAnim->add("run", 2.f, 16.f, 500.f, 0.f);
    playerAnim->add("damage", 1.f, 10.f, 650.f, 1.f);
    playerAnim->add("death", 2.f, 20.f, 530.f, 1.f);
    playerAnim->add("stance", 1.f, 20.f, 580.f, 0.f);
//    playerAnim->add("leftpunch", 4.f, leftPunchFrames, 690.f, 0.f);
//    playerAnim->add("rightpunch", 4.f, rightPunchFrames, 670.f, 0.f);
    playerAnim->add("shieldup", 1.f, 10.f, 710.f, 0.f);
    playerAnim->add("shieldwalk", 1.f, 20.f, 730.f, 0.f);
    playerAnim->add("shieldidle", 1.f, 100.f, 760.f, 0.f);
    playerAnim->add("shieldamage", 1.f, 10.f, 880.f, 1.f);
    playerAnim->add("pickup", 1.f, 20.f, 960.f, 1.f);
    playerAnim->add("attackright", 1.f, 10.f, 930.f, 1.f);
//    playerAnim->add("stomp", 4.f, stompFrames, 900.f, 0.f);
    playerAnim->add("meditatestart", 1.f, 20.f, 1000.f, 1.f);
    playerAnim->add("meditate", 1.f, 99.f, 1030.f, 0.f);

}

//void makePlayerAnimations::makePlayerAttackAnimations(std::shared_ptr<AnimationComponent> &playerAnim,
//                                                      std::shared_ptr<PlayerAbilityComponent){
//    float leftPunchFrames = 10.f;
//    float leftPunchTime = getAttackFrameSpeed(AbilityConstants::LEFT_ATTACK_SPEED, leftPunchFrames);

//    float rightPunchFrames = 10.f;
//    float rightPunchTime =getAttackFrameSpeed(AbilityConstants::RIGHT_ATTACK_SPEED, leftPunchFrames);

//    float stompFrames = 17.f;
//    float stompTime = getAttackFrameSpeed(AbilityConstants::STOMP_ATTACK_SPEED, stompFrames);

//    playerAnim->add("leftpunch", leftPunchTime, leftPunchFrames, 690.f, 0.f);
//    playerAnim->add("rightpunch", rightPunchTime, rightPunchFrames, 670.f, 0.f);
//    playerAnim->add("stomp", stompTime, stompFrames, 900.f, 0.f);
//}

void MainScreen::makeUI(std::shared_ptr<GameObject> &player){

    std::shared_ptr<UIDrawSystem> uiDrawSystem = std::make_shared<UIDrawSystem>(m_camera);
    std::shared_ptr<UITickSystem> uiTickSystem = std::make_shared<UITickSystem>();
    std::shared_ptr<UIComponent> uiComponent = std::make_shared<UIComponent>();

    //health & stamina bar panel
    std::shared_ptr<UIPanel> barPanel = std::make_shared<UIPanel>(0.4f, 0.2f, 0.f, 0.f);
    std::shared_ptr<ShapeUI> healthBar = std::make_shared<ShapeUI>(glm::vec3(0.f, 1.f, 0.f), "healthBar", "uiquad", glm::vec3(0.1f, 0.1f, 0.f), glm::vec3(0.7, 0.2, 1.f));
    std::function<void(ShapeUI&)> healthCallBack = [player](ShapeUI &shape) {
        std::shared_ptr<PlayerAbilityComponent> playerAbilityComponent = player->getComponent<PlayerAbilityComponent>();
        float currentHealth = playerAbilityComponent->getCurrentHealth();
        float maxHealth = playerAbilityComponent->getMaxHealth();
        shape.setScaleX(currentHealth/maxHealth);
    };
    healthBar->setCallback(healthCallBack);
    std::shared_ptr<UIElement> uiHealth = std::dynamic_pointer_cast<UIElement>(healthBar);
    barPanel->addUIElement(0, "healthBar", uiHealth);
    std::shared_ptr<ShapeUI> staminaBar = std::make_shared<ShapeUI>(glm::vec3(0.f, 0.f, 1.f), "staminaBar", "uiquad", glm::vec3(0.1f, 0.4f, 0.f), glm::vec3(0.7, 0.2, 1.f));
    std::function<void(ShapeUI&)> staminaCallBack = [player](ShapeUI &shape) {
        std::shared_ptr<PlayerAbilityComponent> playerAbilityComponent = player->getComponent<PlayerAbilityComponent>();
        float currentStamina = playerAbilityComponent->getCurrentStamina();
        float maxStamina = playerAbilityComponent->getMaxStamina();
        shape.setScaleX(currentStamina/maxStamina);
    };
    staminaBar->setCallback(staminaCallBack);
    std::shared_ptr<UIElement> uiStamina = std::dynamic_pointer_cast<UIElement>(staminaBar);
    barPanel->addUIElement(1, "staminaBar", uiStamina);
    uiComponent->addPanel("barPanel", barPanel);

    //health & stamina bar panel
    std::shared_ptr<UIPanel> levelPanel = std::make_shared<UIPanel>(0.4f, 0.2f, 0.6f, 0.f);
    std::shared_ptr<ShapeUI> levelBar = std::make_shared<ShapeUI>(glm::vec3(1.f, 0.f, 0.f), "levelBar", "uiquad", glm::vec3(0.2f, 0.4f, 0.f), glm::vec3(0.7, 0.18, 1.f));
    std::function<void(ShapeUI&)> levelBarCallBack = [player](ShapeUI &shape) {
        std::shared_ptr<PlayerLevelComponent> playerLevelComponent = player->getComponent<PlayerLevelComponent>();
        float currentExperience = playerLevelComponent->getProgressTowardNextLevelExperience();
        float maxExperience = playerLevelComponent->getTotalExperienceNeededForNextLevel();
        shape.setScaleX(currentExperience/maxExperience);
    };
    levelBar->setCallback(levelBarCallBack);
    std::shared_ptr<TextUI> levelInfo = std::make_shared<TextUI>("Level: ", 0.05f, glm::vec3(1.f), glm::vec3(0.2f, 0.27f, 0.f));
    std::shared_ptr<TextUI> levelNum = std::make_shared<TextUI>("0", 0.05f, glm::vec3(1.f), glm::vec3(0.50f, 0.27f, 0.f));
    std::shared_ptr<UIElement> uiLevel = std::dynamic_pointer_cast<UIElement>(levelInfo);
    std::function<void(TextUI&)> levelCallBack = [player](TextUI &text) {
        std::shared_ptr<PlayerLevelComponent> playerLevelComponent = player->getComponent<PlayerLevelComponent>();
        int currentLevel = playerLevelComponent->getCurrentLevel();
        text.setText(std::to_string(currentLevel));
    };
    levelNum->setCallback(levelCallBack);
    std::shared_ptr<UIElement> uiLevelNum = std::dynamic_pointer_cast<UIElement>(levelNum);
    std::shared_ptr<UIElement> uiLevelBar = std::dynamic_pointer_cast<UIElement>(levelBar);
    levelPanel->addUIElement(1, "levelNum", uiLevelNum);
    levelPanel->addUIElement(0, "level", uiLevel);
    levelPanel->addUIElement(2, "levelBar", uiLevelBar);
    uiComponent->addPanel("levelPanel", levelPanel);
    uiComponent->getPanel("levelPanel")->callbackAll();

    //attacks panel
    std::shared_ptr<UIPanel> attackPanel = std::make_shared<UIPanel>(0.3f, 0.2f, 0.7f, 0.8f);
    std::shared_ptr<ShapeUI> attackSelect = std::make_shared<ShapeUI>(glm::vec3(1.f, 0.f, 0.f), "attackSelect", "uiquad", glm::vec3(0.09f, 0.08f, 0.f), glm::vec3(0.27, 0.54, 1.f));
    std::shared_ptr<UIElement> uiAttackSelect = std::dynamic_pointer_cast<UIElement>(attackSelect);
    attackPanel->addUIElement(0, "attackSelect",uiAttackSelect);
    std::function<void(ShapeUI&)> attackCallBack = [player](ShapeUI &shape) {std::string attack = player->getComponent<PlayerAbilityComponent>()->getCurrentAttack();
                                                                             if(!attack.compare("leftpunch")){
                                                                                 shape.setPosition(glm::vec3(0.09f, 0.08f, 0.f));
                                                                             }
                                                                             else if(!attack.compare("rightpunch")){
                                                                                 shape.setPosition(glm::vec3(0.39f, 0.08f, 0.f));
                                                                             }
                                                                             else{
                                                                                 shape.setPosition(glm::vec3(0.69f, 0.08f, 0.f));
                                                                             }
    };
    attackSelect->setCallback(attackCallBack);
    std::shared_ptr<ShapeUI> attack1 = std::make_shared<ShapeUI>("leftpunch", "leftpunch", "uiquad", glm::vec3(0.1f, 0.1f, 0.f), glm::vec3(0.25, 0.5, 1.f));
    std::shared_ptr<UIElement> uiAttack1 = std::dynamic_pointer_cast<UIElement>(attack1);
    attackPanel->addUIElement(1, "attack1",uiAttack1);
    std::shared_ptr<ShapeUI> attack2 = std::make_shared<ShapeUI>("rightpunch", "rightpunch", "uiquad", glm::vec3(0.4f, 0.1f, 0.f), glm::vec3(0.25, 0.5, 1.f));
    std::shared_ptr<UIElement> uiAttack2 = std::dynamic_pointer_cast<UIElement>(attack2);
    attackPanel->addUIElement(2, "attack2", uiAttack2);
    std::shared_ptr<ShapeUI> attack3 = std::make_shared<ShapeUI>("stomp", "stomp", "uiquad", glm::vec3(0.7f, 0.1f, 0.f), glm::vec3(0.25, 0.5, 1.f));
    std::shared_ptr<UIElement> uiAttack3 = std::dynamic_pointer_cast<UIElement>(attack3);
    attackPanel->addUIElement(3, "attack3",uiAttack3);
    uiComponent->addPanel("attackPanel", attackPanel);

    player->addComponent<UIComponent>(uiComponent);
    uiDrawSystem->addComponent(uiComponent, TypeID::value<UIComponent>());
    uiTickSystem->addComponent(uiComponent, TypeID::value<UIComponent>());
    m_gameWorld->addDrawSystem(uiDrawSystem);
    m_gameWorld->addTickSystem(uiTickSystem);
}

void MainScreen::setColor(glm::vec3 color){
    m_playerColor = color;
}
