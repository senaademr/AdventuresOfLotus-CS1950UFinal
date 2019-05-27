#include "enemygenerator.h"

#include "engine/map_generation/compoundnoise.h"
#include "engine/basics/input.h"
#include "engine/basics/gameobject.h"
#include "engine/components/objectdrawcomponent.h"
#include "engine/components/collisioncomponent.h"
#include "engine/components/animationcomponent.h"
#include "engine/components/transformcomponent.h"
#include "engine/components/physicscomponent.h"
#include "engine/components/collisionresponsecomponent.h"
#include "engine/components/continuouscollisioncomponent.h"
#include "engine/components/timeremovecomponent.h"
#include "engine/components/uicomponent.h"

#include "engine/Animation/mesh.h"
#include "final/final_components/collision_components/cylindercollisioncomponent.h"
#include "final/final_components/enemy_components/enemymovecomponent.h"
#include "final/final_components/enemy_components/enemycollisionresponsecomponent.h"
#include "final/final_components/enemy_components/enemyaicomponent.h"
#include "final/final_components/enemy_components/enemyairesponsecomponent.h"
#include "final/final_components/enemy_components/enemyabilitycomponent.h"
#include "final/final_components/player_components/dynamicmovecomponent.h"
#include <ctime>
#include <cstdlib>

#include "engine/UI/uipanel.h"
#include "engine/UI/shapeui.h"
#include "engine/basics/gameworld.h"

EnemyGenerator::EnemyGenerator(std::shared_ptr<CompoundNoise> noise, std::shared_ptr<NavigationMesh> navmesh,
                               std::shared_ptr<GameWorld> gameWorld, std::shared_ptr<TransformComponent> playerTransform) :
    m_noise(noise),
    m_navmesh(navmesh),
    m_gameWorld(gameWorld),
    m_playerTransform(playerTransform),
    m_currentTime(0.f)
{
  std::string nameMagma("/course/cs195u/.archive/cur/student/gsymeshes/MagmaElemental.fbx");
    loadEnemy(nameMagma, "magma");

  std::string nameSpace("/course/cs195u/.archive/cur/student/gsymeshes/SpaceElemental.fbx");
    loadEnemy(nameSpace, "space");

  std::string nameSpider("/course/cs195u/.archive/cur/student/gsymeshes/Spider.fbx");
    loadEnemy(nameSpider, "spider");
}

EnemyGenerator::~EnemyGenerator() {

}

void EnemyGenerator::tick(float seconds){
    m_currentTime += seconds;
//    std::cout << "time: " << m_currentTime << std::endl;
    if(Input::getGlobalInstance()->isKeyJustPressed(Qt::Key_M)){
        m_currentTime += 60.f;
    }
}

void EnemyGenerator::makeEnemies(const glm::vec3 &topLeft, const float &generationChancePerEnemy, const float &dimension,
                                 int maxAmount, QList<std::shared_ptr<GameObject>> &enemyList){
    while (maxAmount > 0) {
        maxAmount--;
        if (rand() < (1.f-generationChancePerEnemy)*RAND_MAX) {
            continue;
        }

        std::shared_ptr<GameObject> enemy = std::make_shared<GameObject>();
        glm::vec3 pos = setEnemyPosition(enemy, topLeft, dimension);

        std::string environment = m_noise->getEnvironment(pos);

        createEnemy(enemy, environment, pos);
        enemyList.append(enemy);
    }
}

void EnemyGenerator::createEnemy(std::shared_ptr<GameObject> &enemy, std::string &environment, glm::vec3 pos) {
    std::vector<std::string> enemyInfo = getEnemy(environment);
    std::string enemyName = enemyInfo[0];
    std::string environmentMaterial = enemyInfo[1];

    std::shared_ptr<Mesh> currentEnemy = m_enemyMap[enemyName];
    std::shared_ptr<Mesh> copyEnemy = std::make_shared<Mesh>(*currentEnemy);
    std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>();
    transformComponent->setPosition(pos);
    enemy->addComponent<TransformComponent>(transformComponent);
    std::shared_ptr<AnimationComponent> animationComponent = std::make_shared<AnimationComponent>(copyEnemy, environmentMaterial);
    float drawScale = getDrawScale(enemyName);
    animationComponent->setDrawScale(drawScale);
    std::shared_ptr<ObjectDrawComponent> objectDraw = std::make_shared<ObjectDrawComponent>();
    objectDraw->setMaterial("redTransparent");

    glm::vec3 boundingCylinder = getBoundingCylinder(enemyName, drawScale);
    transformComponent->setSize(boundingCylinder);
    std::shared_ptr<ContinuousCollisionComponent> continousComponent = std::make_shared<ContinuousCollisionComponent>(transformComponent);
    enemy->addComponent<ContinuousCollisionComponent>(continousComponent);
    //std::shared_ptr<EnemyMoveComponent> move = std::make_shared<EnemyMoveComponent>(m_playerTransform, m_navmesh, enemyName);
    std::shared_ptr<PhysicsComponent> physics = std::make_shared<PhysicsComponent>();
    std::shared_ptr<CollisionComponent> collisionComponent = std::make_shared<CylinderCollisionComponent>();
    std::shared_ptr<CollisionResponseComponent> collisionResponseComponent = std::make_shared<EnemyCollisionResponseComponent>(); // enemy response
    std::shared_ptr<TimeRemoveComponent> timeRemove = std::make_shared<TimeRemoveComponent>(m_gameWorld, getDeathAnimationTime(enemyName));
    timeRemove->setisTimerOn(false);
    std::shared_ptr<EnemyAbilityComponent> enemyAbilityComponent = getEnemyAbilityComponent(enemyName);
    std::shared_ptr<EnemyAIResponseComponent> enemyAIReponseComponent = std::make_shared<EnemyAIResponseComponent>(m_playerTransform, m_navmesh, enemyName);
    std::shared_ptr<EnemyAIComponent> enemyAIComponent = std::make_shared<EnemyAIComponent>(enemyAIReponseComponent);
    std::shared_ptr<DynamicMoveComponent> dynamicMove = std::make_shared<DynamicMoveComponent>(20.f, 100.f, enemyAbilityComponent->getMovementSpeed());

    std::shared_ptr<UIComponent> ui = std::make_shared<UIComponent>();
    std::shared_ptr<UIPanel> enemyHealthPanel = std::make_shared<UIPanel>(1.f, 1.f, 0.f, 0.f);
    std::shared_ptr<ShapeUI> healthBar = std::make_shared<ShapeUI>(glm::vec3(1.f, 0.f, 0.f), "healthEnemyBar", "uiquad", glm::vec3(pos), glm::vec3(0.1f, 0.02f, 0.f));
    healthBar->setOrthographic(true);
    std::function<void(ShapeUI&)> healthCallBack = [enemy, enemyName](ShapeUI &shape) {
        std::shared_ptr<EnemyAbilityComponent> enemyAbilityComponent = enemy->getComponent<EnemyAbilityComponent>();
        float currentHealth = enemyAbilityComponent->getCurrentHealth();
        float maxHealth = enemyAbilityComponent->getMaxHealth();
        shape.setScaleX(currentHealth/maxHealth);
        std::shared_ptr<TransformComponent> transformComponent = enemy->getComponent<TransformComponent>();
        std::shared_ptr<AnimationComponent> anim = enemy->getComponent<AnimationComponent>();
//        glm::vec3 pos = transformComponent->getPosition();
//        pos.y += 5.f;
//        pos.x += 2.f;
        glm::vec3 pos = getHealthUIPos(enemyName, transformComponent, anim);
        shape.setPosition(pos);
    };
    healthBar->setCallback(healthCallBack);
    std::shared_ptr<UIElement> uihealthBar = std::dynamic_pointer_cast<UIElement>(healthBar);
    enemyHealthPanel->addUIElement(0, "healthEnemy", uihealthBar);
    ui->addPanel("enemyPanel", enemyHealthPanel);
//    m_gameWorld->

    //enemy->addComponent<EnemyMoveComponent>(move);
    enemy->addComponent<PhysicsComponent>(physics);
    enemy->addComponent<CollisionComponent>(collisionComponent);
    enemy->addComponent<CollisionResponseComponent>(collisionResponseComponent);
    enemy->addComponent<AnimationComponent>(animationComponent);
    enemy->addComponent<TimeRemoveComponent>(timeRemove);
    enemy->addComponent<EnemyAbilityComponent>(enemyAbilityComponent);
    enemy->addComponent<AIResponseComponent>(enemyAIReponseComponent);
    enemy->addComponent<AIComponent>(enemyAIComponent);
    enemy->addComponent<DynamicMoveComponent>(dynamicMove);
    enemy->addComponent<UIComponent>(ui);
}

glm::vec3 EnemyGenerator::getHealthUIPos(std::string enemyName, std::shared_ptr<TransformComponent> transformComponent, std::shared_ptr<AnimationComponent> anim){
    glm::vec3 pos = transformComponent->getPosition();
    glm::vec3 boundingCylinder = getBoundingCylinder(enemyName, anim->getDrawScale().x);
    pos.y += boundingCylinder.y + .5f;

//    if(enemyName.compare("spider") == 0){
//        pos.y += 3.f;
////        pos.x += 2.f;
//    }
//    else if(enemyName.compare("magma") == 0){
//        pos.y += 3.f;
////        pos.x += 2.f;
//    }
//    else if(enemyName.compare("space") == 0){
//        pos.y += 3.f;
////        pos.x += 2.f;
//    }
//    std::cout << "don't recognize enemyName: " << enemyName << std::endl;
    return pos;
}

std::shared_ptr<EnemyAbilityComponent> EnemyGenerator::getEnemyAbilityComponent(std::string enemyName){
    if(enemyName.compare("spider") == 0){
        return getSpiderAbilityComponent();
    }
    else if(enemyName.compare("magma") == 0){
        return getMagmaAbilityComponent();
    }
    else if(enemyName.compare("space") == 0){
        return getSpaceAbilityComponent();

    }
    std::cout << "don't recognize enemyName: " << enemyName << std::endl;
    return nullptr;
}

//health, speed, damage, experience
std::shared_ptr<EnemyAbilityComponent> EnemyGenerator::getSpiderAbilityComponent(){
    float health = 10.f + 10.f *m_currentTime /60.f ;
    float speed = 4.5f + .5f* m_currentTime /60.f;
    float damage = 5.f + 5.f *m_currentTime /60.f;
    float experience = 50.f;
//    std::cout << "Generating spider with: health: " << health << ", speed: " << speed << ", damage: " << damage << " at time: " << m_currentTime << std::endl;
    return std::make_shared<EnemyAbilityComponent>(health, speed, damage, experience);
}

//health, speed, damage, experience
std::shared_ptr<EnemyAbilityComponent> EnemyGenerator::getMagmaAbilityComponent(){
    float health = 30.f + 45.f *m_currentTime /60.f;
    float speed = 3.f + .25f* m_currentTime /60.f;
    float damage = 15.f + 15.f *m_currentTime /60.f;
    float experience = 100.f;
//    std::cout << "Generating magma with: health: " << health << ", speed: " << speed << ", damage: " << damage << " at time: " << m_currentTime << std::endl;

    return std::make_shared<EnemyAbilityComponent>(health, speed, damage, experience);
}

//health, speed, damage, experience
std::shared_ptr<EnemyAbilityComponent> EnemyGenerator::getSpaceAbilityComponent(){
    float health = 20.f + 20.f *m_currentTime /60.f;
    float speed = 6.f + .75f *m_currentTime /60.f;;
    float damage = 10.f + 10.f *m_currentTime /60.f;;
    float experience = 150.f;
//    std::cout << "Generating space with: health: " << health << ", speed: " << speed << ", damage: " << damage << " at time: " << m_currentTime << std::endl;

    return std::make_shared<EnemyAbilityComponent>(health, speed, damage, experience);

}

std::vector<std::string> EnemyGenerator::getEnemy(std::string &environment){
    std::string environmentMaterial = "magmaAquatic";
    std::string enemyName = "magma";
    double r = ((double) rand() / (RAND_MAX));

    if(!environment.compare("desert")){
        if(r > 0.5f){
            environmentMaterial = "magmaDesert";
            enemyName = "magma";
        } else {
            environmentMaterial = "spiderDesert";
            enemyName = "spider";
        }
    }
    else if(!environment.compare("mountain")){
        if(r > 0.5f){
            environmentMaterial = "spiderMountain";
            enemyName = "spider";
        } else {
            environmentMaterial = "spaceMountain";
            enemyName = "space";
        }
    }
    else if(!environment.compare("aquatic")){
        if(r > 0.5f){
            environmentMaterial = "magmaAquatic";
            enemyName = "magma";
        } else {
            environmentMaterial = "spaceAquatic";
            enemyName = "space";
        }
    }
    std::vector<std::string> info {enemyName, environmentMaterial};
    return info;
}

float EnemyGenerator::getDeathAnimationTime(std::string name){
    float frames = 0;
    //this looks dumb because it worked fine for it to be the same for all of them
    if(!name.compare("spider")){
        frames = 60;
    }
    else if(!name.compare("space")){
        frames = 60;
    }
    else if(!name.compare("magma")){
        frames = 60;
    }
    return frames/60.f;
}

float EnemyGenerator::getDrawScale(std::string name){
    if(!name.compare("spider")){
        std::normal_distribution<float> spiderDistribution(.015f, .03f);
        float spiderSize = spiderDistribution(m_generator);
        if(spiderSize < .008){
            spiderSize = .008;
        }
        return spiderSize;
    }
    else if(!name.compare("space")){
        std::normal_distribution<float> spaceSizeDistribution(.7f, .1f);
        float spaceSize = spaceSizeDistribution(m_generator);
        return spaceSize;
    }
    else if(!name.compare("magma")){
        std::normal_distribution<float> magmaSizeDistribution(.9f, .2f);
        float magmaSize = magmaSizeDistribution(m_generator);
        return magmaSize;
    }
    return 1.f;
}

glm::vec3 EnemyGenerator::getBoundingCylinder(std::string name, float drawScale){
    if(!name.compare("spider")){
        return glm::vec3(160, 50, 160) * drawScale;
    }
    else if(!name.compare("magma")){
        return glm::vec3(3, 4, 3) * drawScale;
    }
    else if(!name.compare("space")){
        return glm::vec3(1.3, 4, 1.3) * drawScale;
    }

    std::cout << "no matching name for bounding cylinder, returning 1" << std::endl;
    return glm::vec3(1);
}

glm::vec3 EnemyGenerator::setEnemyPosition(std::shared_ptr<GameObject> &enemy, const glm::vec3 &topLeft, const float &dimension) const {
    float r = static_cast<float>(rand())/RAND_MAX; // Random float 0 <= x < 1
    float k = static_cast<float>(rand())/RAND_MAX;
    glm::vec3 position = topLeft +  glm::vec3(r*dimension, 0, k*dimension);
    position.y = m_noise->interpolatedNoise(glm::vec2(position.x, position.z))+ 3;
    return position;
}

void EnemyGenerator::loadEnemy(std::string filename, std::string enemyname) {
    std::shared_ptr<Mesh> enemy = std::make_shared<Mesh>();
    enemy->loadMesh(filename);
    if(!enemyname.compare("spider")){
        enemy->updateAnimation(1, 2.f, 1);
        enemy->updateAnimation(2, 1.5f, 0);
    }
    else if(!enemyname.compare("magma")){
        enemy->updateAnimation(3, 5.f, 1);
        enemy->updateAnimation(9, 3.f, 0);
    }
    else if(!enemyname.compare("space")){
        enemy->updateAnimation(5, 5.f, 1);
        enemy->updateAnimation(2, 2.f, 0);
    }
    m_enemyMap.insert(std::pair<std::string, std::shared_ptr<Mesh>>(enemyname, enemy));
}
