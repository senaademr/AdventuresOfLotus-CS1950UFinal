#include "dcplayerinputcomponent.h"

//#include <math.h>

//#include "engine/basics/input.h"
//#include "engine/components/physicscomponent.h"
//#include "engine/graphics/Camera.h"
//#include "engine/components/transformcomponent.h"
//#include "engine/components/drawable.h"
//#include "engine/components/collisioncomponent.h"
//#include "engine/components/cameracomponent.h"
//#include "engine/components/raycastcomponent.h"
//#include "engine/components/timeremovecomponent.h"
//#include "engine/basics/gameobject.h"
//#include "engine/components/collider/ray.h"
//#include "engine/components/objectdrawcomponent.h"
//#include "engine/basics/gameworld.h"
//#include "dungeon_crawler/components/healthcomponent.h"

//#include "engine/ai/ticktimer.h"

//DCPlayerInputComponent::DCPlayerInputComponent(std::shared_ptr<GameObject> gameObject,
//                                               std::shared_ptr<GameWorld> gameWorld, std::shared_ptr<Camera> camera)
//    : Component(gameObject, ComponentType::PLAYER_INPUT),
//      Tickable(),
//      m_gameWorld(gameWorld),
//      m_camera(camera),
//      m_input(Input::getGlobalInstance()),
//      m_bulletTimer(nullptr),
//      m_velocity(3.f),
//      m_bulletSpeed(6.f),
//      m_jumpSpeed(4.f),
//      m_canJump(false),
//      m_canFly(false)
//{
//    m_bulletTimer = std::make_shared<TickTimer>(.5f, false);
//}

//void DCPlayerInputComponent::tick(float seconds){
//    m_bulletTimer->tick(seconds);
//    std::shared_ptr<GameObject> gameObject = this->getGameObject();
//    std::shared_ptr<TransformComponent> transformComponent =
//            gameObject->getComponent<TransformComponent>(ComponentType::POSITION);
//    assert(transformComponent != nullptr);
//    //std::cout << "Player position: " << TransformComponent::positionToString(TransformComponent->getPosition()) << std::endl;
//    glm::vec3 look = m_camera->getLook();
//    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
//    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);

//    std::shared_ptr<PhysicsComponent> physicsComponent = gameObject->getComponent<PhysicsComponent>(ComponentType::PHYSICS);
//    glm::vec3 newVelocity = glm::vec3(0, 0, 0);

//    if(m_input->isKeyDown(Qt::Key_W)) newVelocity += dir * m_velocity;
//    if(m_input->isKeyDown(Qt::Key_S)) newVelocity += -dir * m_velocity;
//    if(m_input->isKeyDown(Qt::Key_A)) newVelocity += perp * m_velocity;
//    if(m_input->isKeyDown(Qt::Key_D)) newVelocity += -perp * m_velocity;
//    physicsComponent->setXVelocity(newVelocity.x);
//    physicsComponent->setZVelocity(newVelocity.z);

////    if(inSimilarYPosition(transformComponent->getPosition())){
////        m_canJump = true;
////    }
//    if(m_input->isKeyDown(Qt::Key_Space) && m_canJump){
//        physicsComponent->setYVelocity(m_jumpSpeed);
//        m_canJump = false;
//    }
//    if(m_input->isKeyDown(Qt::Key_Shift) && m_canJump){
//        std::cout << "super jump" << std::endl;
//        physicsComponent->setYVelocity(2.3f*m_jumpSpeed);
//        m_canJump = false;
//    }
//    if(m_input->isMouseJustPressed(Qt::LeftButton)){
//        castRay();
//    }
//    if(m_input->isMousePressed(Qt::LeftButton)){
//        if( m_bulletTimer->isTime()){
//            shootBullet();
//        }
//    }
//    if(m_input->isMouseJustPressed(Qt::RightButton)){
//        changeShape();
//    }
//    if(m_input->isKeyJustPressed(Qt::Key_G)){
//        physicsComponent->setGravity(m_canFly);
//        m_canFly = !m_canFly;
//    }
//    if(m_input->isKeyJustPressed(Qt::Key_0)){
//        m_velocity *= 1.1;
//    }
//    if(m_input->isKeyJustPressed(Qt::Key_9)){
//        m_velocity /= 1.1;
//    }
//    if(m_input->isKeyJustPressed(Qt::Key_B)){
//        std::shared_ptr<HealthComponent> health = getGameObject()->getComponent<HealthComponent>(ComponentType::HEALTH);
//        health->dealDamage(99);
//    }

//    if(m_input->isKeyJustPressed(Qt::Key_R)){
//        transformComponent->setPosition(glm::vec3(24.f/2.f + .5f, 1, .5f));
//        physicsComponent->setVelocity(glm::vec3(0));
//    }



//    if(m_canFly){
//        if(m_input->isKeyDown(Qt::Key_Up)){
//            physicsComponent->setYVelocity(m_velocity);
//        }
//        else if(m_input->isKeyDown(Qt::Key_Down)){
//            physicsComponent->setYVelocity(-m_velocity);
//        }
//        else{
//            physicsComponent->setYVelocity(0);
//        }
//    }



//}
//void DCPlayerInputComponent::setCanJump(bool canJump){
//    m_canJump = canJump;
//}

//void DCPlayerInputComponent::shootBullet(){
//    //std::cout << "shooting bullet" << std::endl;
//    std::shared_ptr<GameObject> bullet = std::make_shared<GameObject>();
//    std::shared_ptr<ObjectDrawComponent> drawComponent = std::make_shared<ObjectDrawComponent>(bullet);
//    drawComponent->setShapeType("sphere");
//    drawComponent->setMaterial("bullet");
//    Ray ray = getRay();
//    std::shared_ptr<PhysicsComponent> physicsComponent = std::make_shared<PhysicsComponent>(bullet);
//    physicsComponent->setGravity(false);
//    physicsComponent->setVelocity(m_bulletSpeed* ray.getDirection());
//    //physicsComponent->setGravity();
//    std::shared_ptr<TransformComponent> transformComponent
//            = std::make_shared<TransformComponent>(bullet);
//    auto playerTransformComponent = getGameObject()->getComponent<TransformComponent>(ComponentType::POSITION);
//    transformComponent->setPosition(ray.getOrigin() + glm::vec3(0, playerTransformComponent->getSize().y, 0));
//    transformComponent->setSize(glm::vec3(.09));
//    std::shared_ptr<TimeRemoveComponent> timeRemove = std::make_shared<TimeRemoveComponent>(bullet, m_gameWorld, 3);

//    bullet->addComponent(drawComponent);
//    bullet->addComponent(transformComponent);
//    bullet->addComponent(physicsComponent);
//    bullet->addComponent(timeRemove);
//    std::shared_ptr<CollisionComponent> collisionComponent
//            = std::make_shared<CollisionComponent>(bullet, transformComponent, ColliderType::BOX);
//    collisionComponent->setResponse(std::make_shared<BulletCollisionResponseComponent>(bullet, m_gameWorld));
//    bullet->addComponent(collisionComponent);

//    m_gameWorld->addObject(bullet);
//}

//Ray DCPlayerInputComponent::getRay(){
//    auto gameObject = getGameObject();
//    std::shared_ptr<CameraComponent> camera = gameObject->getComponent<CameraComponent>(ComponentType::CAMERA);
//    std::shared_ptr<RaycastComponent> rayCast = gameObject->getComponent<RaycastComponent>(ComponentType::RAY);
//    assert(camera);
//    assert(rayCast);
//    glm::vec3 look = camera->getCameraDirection();
//    std::shared_ptr<TransformComponent> transformComponent =
//            gameObject->getComponent<TransformComponent>(ComponentType::POSITION);
//    glm::vec3 start = transformComponent->getPosition();
//    glm::vec3 origin = start + getRayDisplacement(transformComponent, look);
//    return Ray(origin, look);
//}

//void DCPlayerInputComponent::castRay(){
//    auto gameObject = getGameObject();
//    //std::cout << "casting ray!" << std::endl;
////    std::shared_ptr<CameraComponent> camera = gameObject->getComponent<CameraComponent>(ComponentType::CAMERA);
//    //    std::shared_ptr<RaycastComponent> rayCast = gameObject->getComponent<RaycastComponent>(ComponentType::RAY);
////    assert(camera);
////    assert(rayCast);
////    glm::vec3 look = camera->getCameraDirection();
////    std::shared_ptr<TransformComponent> transformComponent =
////            gameObject->getComponent<TransformComponent>(ComponentType::POSITION);
////    glm::vec3 start = transformComponent->getPosition();
////    glm::vec3 origin = start + getRayDisplacement(transformComponent, look);
//    //glm::vec3 origin = start;
//    std::shared_ptr<RaycastComponent> rayCast = gameObject->getComponent<RaycastComponent>(ComponentType::RAY);
//    Ray ray = getRay();

//    std::shared_ptr<CollisionComponent> objectCollided = rayCast->rayCast(ray);
//    if(objectCollided != nullptr){
//        std::cout << "Ray collision!" << std::endl;
//        std::shared_ptr<ObjectDrawComponent> draw =
//                objectCollided->getGameObject()->getComponent<ObjectDrawComponent>(ComponentType::DRAW);
//        if(draw->getMaterial() != "red"){
//            draw->setMaterial("red");
//        }
//        else{
//            draw->setMaterial("green");
//        }
//    }

//}

//glm::vec3 DCPlayerInputComponent::getRayDisplacement(std::shared_ptr<TransformComponent> transformComponent, glm::vec3 look){
//    glm::vec3 lookNorm = glm::normalize(look);

//    float delta = .001;
//    glm::vec3 objectSize = transformComponent->getTransform().getSize();
//    float translateDistance = glm::max(objectSize.x, objectSize.y);
//    translateDistance = glm::max(translateDistance, objectSize.z);
//    translateDistance += delta;
//    translateDistance = objectSize.x * 1.3f;
//    return lookNorm * translateDistance;
//}


//void DCPlayerInputComponent::changeShape(){
//    std::shared_ptr<ObjectDrawComponent> draw = this->getGameObject()->getComponent<ObjectDrawComponent>(ComponentType::DRAW);
//    std::shared_ptr<CollisionComponent> collision = this->getGameObject()->getComponent<CollisionComponent>(ComponentType::COLLISION);
//    std::shared_ptr<TransformComponent> transform = this->getGameObject()->getComponent<TransformComponent>(ComponentType::POSITION);
//    std::string shape = draw->getShapeType();
//    if(shape.compare("cube") == 0){
//        draw->setShapeType("cylinder");
//        collision->setCollider(ColliderType::CYLINDER, transform);
//    }
//    else if(shape.compare("cylinder") == 0){
//        draw->setShapeType("sphere");
//        collision->setCollider(ColliderType::SPHERE, transform);
//    }
//    else if(shape.compare("sphere") == 0){
//        draw->setShapeType("cube");
//        collision->setCollider(ColliderType::BOX, transform);
//    }
//    else{
//        std::cout << "invalid shape type: " << shape << std::endl;
//        throw -1;
//    }
//}

//void DCPlayerInputComponent::setFlight(bool canFly){
//    m_canFly = canFly;
//}
