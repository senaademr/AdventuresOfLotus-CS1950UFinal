#include "playercontrolcomponent.h"

#include "engine/basics/gameobject.h"
#include "engine/basics/gameworld.h"
#include "engine/components/transformcomponent.h"
#include "engine/components/uicomponent.h"
#include "engine/components/animationcomponent.h"
#include "engine/components/physicscomponent.h"
#include "engine/components/objectdrawcomponent.h"
#include "engine/components/collisioncomponent.h"
#include "engine/components/collisionresponsecomponent.h"
#include "engine/components/continuouscollisioncomponent.h"
#include "engine/components/timeremovecomponent.h"
#include "final/final_components/collision_components/spherecollisioncomponent.h"
#include "final/final_components/player_components/deathcomponent.h"
#include "final/final_components/collision_components/bulletcollisionresponsecomponent.h"
#include "final/final_components/collision_components/impactbulletcollisionresponsecomponent.h"
#include "final/final_components/player_components/dynamicmovecomponent.h"
#include "final/final_components/player_components/playerlevelcomponent.h"
#include "engine/UI/uipanel.h"

#include "engine/graphics/Camera.h"
#include "engine/basics/input.h"
#include "engine/map_generation/valuenoise.h"
#include "engine/util/CommonIncludes.h"
#include "engine/util/ticktimer.h"
#include "engine/util/util.h"

#include "final/final_components/player_components/playerabilitycomponent.h"

PlayerControlComponent::PlayerControlComponent(std::shared_ptr<Camera> camera, std::shared_ptr<GameWorld> gameWorld)
    : m_camera(camera),
      m_gameWorld(gameWorld),
      m_attackTimer(std::make_shared<TickTimer>(1.f, false)),
      m_input(Input::getGlobalInstance())
{

}


void PlayerControlComponent::tick(float seconds){
    std::shared_ptr<GameObject> gameObject = this->getGameObject();
    m_attackTimer->tick(seconds);

    if(gameObject->getComponent<PlayerAbilityComponent>()->isDead()){
        m_deathCount++;
        if(m_deathCount == 95){
            gameObject->getComponent<DeathComponent>()->callGameOver();
        }
        return;
    }

    handleAttackSwitch();
    handleJump();
    handleMeditation(seconds);
    bool isMoving = handleMovement(seconds);


    if(m_input->isMousePressed(Qt::LeftButton)){
        if(m_isMeditating){
            m_isMeditating = false;
        }
        std::string currentAttack = gameObject->getComponent<PlayerAbilityComponent>()->getCurrentAttack();
        gameObject->getComponent<AnimationComponent>()->changeCurrentAnimation(currentAttack);
        makeAttack();
    }

    else if(!isMoving && !m_isJumping && !m_isMeditating){
        gameObject->getComponent<AnimationComponent>()->changeCurrentAnimation("idle1");
    }

    if(m_input->isKeyJustPressed(Qt::Key_PageUp)){
//        gameObject->getComponent<PlayerAbilityComponent>()->incrementNumberAttacks();
        gameObject->getComponent<PlayerLevelComponent>()->addExperience(gameObject->getComponent<PlayerLevelComponent>()->getTotalExperienceNeededForNextLevel());
    }


    if(m_input->isKeyDown(Qt::Key_R)) gameObject->getComponent<TransformComponent>()->setY(100);
    /***************** end debugging controls *******************/
}

void PlayerControlComponent::handleJump(){
    std::shared_ptr<GameObject> gameObject = this->getGameObject();
    std::shared_ptr<PhysicsComponent> physicsComponent
            = gameObject->getComponent<PhysicsComponent>();

    bool isSpace = m_input->isKeyDown(Qt::Key_Space);
    if(isSpace && !m_isJumping){
        float sprintmodifier = 1.f;
        if(m_isSprinting){
            sprintmodifier = 2.f;
        }
        physicsComponent->setYVelocity(m_jumpVelocity* sprintmodifier);
        m_isJumping = true;
        if(m_isMeditating){
            m_isMeditating = false;
        }
    }
//    if(physicsComponent->getVelocity().y < -m_jumpVelocity && m_isJumping){
//        m_isJumping = false;
//    }
    if(physicsComponent->getVelocity().y < 0.f && m_isJumping){
        gameObject->getComponent<AnimationComponent>()->changeCurrentAnimation("freefall");
    }
    else if(m_isJumping){
        gameObject->getComponent<AnimationComponent>()->changeCurrentAnimation("jump");
    }
}

void PlayerControlComponent::handleAttackSwitch(){
    updateAttackTimer();
    std::shared_ptr<GameObject> gameObject = this->getGameObject();
    if(m_input->isKeyJustPressed(Qt::Key_E) || m_input->isKeyJustPressed(Qt::Key_Right)){
        gameObject->getComponent<PlayerAbilityComponent>()->switchAttack(true);
        gameObject->getComponent<UIComponent>()->getPanel("attackPanel")->callbackOne("attackSelect");
    }
    if(m_input->isKeyJustPressed(Qt::Key_Q) ||m_input->isKeyJustPressed(Qt::Key_Left)){
        gameObject->getComponent<PlayerAbilityComponent>()->switchAttack(false);
        gameObject->getComponent<UIComponent>()->getPanel("attackPanel")->callbackOne("attackSelect");

    }
}

void PlayerControlComponent::updateAttackTimer(){
    std::shared_ptr<PlayerAbilityComponent> playerAbility = getGameObject()->getComponent<PlayerAbilityComponent>();
    std::string attackName = playerAbility->getCurrentAttack();
    m_attackTimer->setSecondsUntilTrue(playerAbility->getAttackSpeed(attackName));
//    if(attackName.compare("leftpunch") == 0){
//        m_attackTimer->setSecondsUntilTrue(AbilityConstants::LEFT_ATTACK_SPEED);
//        //m_attackTimer->reset();
//    }
//    if(attackName.compare("rightpunch") == 0){
//        m_attackTimer->setSecondsUntilTrue(AbilityConstants::RIGHT_ATTACK_SPEED);
//        //m_attackTimer->reset();
//    }
//    if(attackName.compare("stomp") == 0){
//        m_attackTimer->setSecondsUntilTrue(AbilityConstants::STOMP_ATTACK_SPEED);
//        //m_attackTimer->reset();
//    }
}

bool PlayerControlComponent::handleMovement(float seconds){
    std::shared_ptr<GameObject> gameObject = this->getGameObject();
    glm::vec3 newVelocity = glm::vec3(0, 0, 0);

    bool isUp = m_input->isKeyDown(Qt::Key_W);
    bool isDown = m_input->isKeyDown(Qt::Key_S);
    bool isRight = m_input->isKeyDown(Qt::Key_D);
    bool isLeft = m_input->isKeyDown(Qt::Key_A);
    bool isMoving = isUp || isDown || isRight || isLeft;
    bool isShift = m_input->isKeyDown(Qt::Key_Shift);
    bool isClick = m_input->isMousePressed(Qt::LeftButton);
    if(m_isSprinting){
        if(gameObject->getComponent<PlayerAbilityComponent>()->getCurrentStamina() <= 0
                || m_isMeditating
                || ! isShift){
            m_isSprinting = false;
        } else {
            gameObject->getComponent<PlayerAbilityComponent>()->addToCurrentStamina(-15.f * seconds);
            gameObject->getComponent<UIComponent>()->getPanel("barPanel")->callbackAll();
        }
    }
    std::shared_ptr<PlayerAbilityComponent> playerAbility = gameObject->getComponent<PlayerAbilityComponent>();
    if(isShift && playerAbility->getCurrentStamina() > 5){
        m_isSprinting = true;
    }
//    if(!m_isSprinting && isShift && /*(playerAbility->getCurrentStamina() >= playerAbility->getMaxStamina())*/ && isMoving){
//        m_isSprinting = true;
//    }

    if(isMoving){
        if(m_isMeditating){
            m_isMeditating = false;
        }
    }
    if(!m_isSprinting){
        std::shared_ptr<PlayerAbilityComponent> playerAbility = gameObject->getComponent<PlayerAbilityComponent>();
        if(playerAbility->getCurrentStamina()< playerAbility->getMaxStamina()){
            playerAbility->addToCurrentStamina(playerAbility->getPassiveStaminaRegenRate() * seconds);
        }
    }

    float yaw = m_camera->getYaw();
    glm::vec3 look = m_camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);
    float movementSpeed = playerAbility->getMovementSpeed();
    gameObject->getComponent<TransformComponent>()->setRotation(yaw+glm::radians(0.f), glm::vec3(0,1,0));
    if(isRight){
        newVelocity += -perp * movementSpeed;
        gameObject->getComponent<TransformComponent>()->setRotation(yaw+glm::radians(270.f), glm::vec3(0,1,0));
    }
    if(isUp){
        newVelocity += dir * movementSpeed;
        gameObject->getComponent<TransformComponent>()->setRotation(yaw, glm::vec3(0,1,0));
    }
    if(isDown){
        newVelocity += -dir * movementSpeed;
        gameObject->getComponent<TransformComponent>()->setRotation(yaw+glm::radians(180.f), glm::vec3(0,1,0));
    }
    if(isLeft){
        newVelocity += perp * movementSpeed;
        gameObject->getComponent<TransformComponent>()->setRotation(yaw+glm::radians(90.f), glm::vec3(0,1,0));
    }
    if(isDown){
        if(m_isSprinting && isShift && !m_isJumping && !isClick){
            gameObject->getComponent<AnimationComponent>()->changeCurrentAnimation("run");  //backwardrun?
        }
        else if(!m_isJumping&& !isClick){
            gameObject->getComponent<AnimationComponent>()->changeCurrentAnimation("backwardWalk");
        }
    }
    else if(isMoving){
        if(m_isSprinting && isShift && !m_isJumping&& !isClick){
            gameObject->getComponent<AnimationComponent>()->changeCurrentAnimation("run");
        }
        else if(!m_isJumping&& !isClick){
            gameObject->getComponent<AnimationComponent>()->changeCurrentAnimation("walk");
        }
    }
    if((isUp && isRight) ){
        gameObject->getComponent<TransformComponent>()->setRotation(yaw+glm::radians(315.f), glm::vec3(0,1,0));
    }
    else if(isDown && isLeft){
        gameObject->getComponent<TransformComponent>()->setRotation(yaw+glm::radians(135.f), glm::vec3(0,1,0));
    }
    else if((isDown && isRight)){
        gameObject->getComponent<TransformComponent>()->setRotation(yaw+glm::radians(225.f), glm::vec3(0,1,0));
    }
    else if((isUp && isLeft)){
        gameObject->getComponent<TransformComponent>()->setRotation(yaw+glm::radians(45.f), glm::vec3(0,1,0));
    }

    std::shared_ptr<DynamicMoveComponent> dynamicMove = m_gameObject->getComponent<DynamicMoveComponent>();
    float sprintConstant = 1.f;
    if(m_isSprinting && isShift){
        sprintConstant = 2.5f;
    }

    dynamicMove->setMaxVelocity(movementSpeed * sprintConstant);

//    glm::vec3 acceleration = sprintConstant* newVelocity;
    dynamicMove->setDesiredDirection(sprintConstant * newVelocity);

    if(isClick){
        gameObject->getComponent<TransformComponent>()->setRotation(yaw, glm::vec3(0,1,0));
//        physicsComponent->setXVelocity(0);
//        physicsComponent->setZVelocity(0);
    }
    return isMoving;
}

void PlayerControlComponent::handleMeditation(float seconds){
    bool isUp = m_input->isKeyDown(Qt::Key_W);
    bool isDown = m_input->isKeyDown(Qt::Key_S);
    bool isRight = m_input->isKeyDown(Qt::Key_D);
    bool isLeft = m_input->isKeyDown(Qt::Key_A);
    bool isMoving = isUp || isDown || isRight || isLeft;
    bool isClick = m_input->isMousePressed(Qt::LeftButton);

    std::shared_ptr<GameObject> gameObject = this->getGameObject();
    bool isOne = m_input->isKeyDown((Qt::Key_1));
    std::shared_ptr<PlayerAbilityComponent> playerAbility = gameObject->getComponent<PlayerAbilityComponent>();
    float health = playerAbility->getCurrentHealth();
    float stamina = playerAbility->getCurrentStamina();
    float maxHealth = playerAbility->getMaxHealth();
    float maxStamina = playerAbility->getMaxStamina();
    if(!isMoving && !isClick &&!m_isJumping && isOne && (health < maxHealth || stamina < maxStamina)){
        gameObject->getComponent<AnimationComponent>()->changeCurrentAnimation("meditate");
        m_isMeditating = true;
    }
    if(m_isMeditating){
        if((health >= maxHealth) && (stamina >= maxStamina) ){
            m_isMeditating= false;
        } else {
            if(health < maxHealth){
                playerAbility->addToCurrentHealth(playerAbility->getMeditationHealthRegenRate() * seconds);
            }
            if(stamina < maxStamina){
                playerAbility->addToCurrentStamina(playerAbility->getMediationStaminaRegenRate() * seconds);
            }
        }
    }

}

glm::vec3 PlayerControlComponent::getAttackSpherePosition(){
    std::shared_ptr<TransformComponent> playerPosition = m_gameObject->getComponent<TransformComponent>();
    glm::vec3 verticalDisplacement = glm::vec3(0, 1, 0);    //bring to height of hand
    glm::vec3 horizontalDisplacement = glm::normalize(glm::vec3(1, 0, 1)* m_camera->getLook());
    glm::vec3 position = playerPosition->getPosition() + verticalDisplacement + horizontalDisplacement;

    return position;
}

glm::vec3 PlayerControlComponent::getAttackVelocity(){
    return m_bulletVelocity * glm::normalize(glm::vec3(1, 1, 1) *m_camera->getLook());
}

void PlayerControlComponent::makeAttack(){
    auto playerAbility = m_gameObject->getComponent<PlayerAbilityComponent>();

    std::string attackName = playerAbility->getCurrentAttack();
    if(m_attackTimer->isTime()){
        if(attackName.compare("leftpunch") == 0){
            m_gameWorld->addObject(getBasicAttack());
        }
        else if (attackName.compare("rightpunch") == 0){
            makeMultiAttack(playerAbility->getNumberAttacks());
        }
        else if(attackName.compare("stomp") == 0){
            makeSlowAttack();
        }
    }
}

void PlayerControlComponent::makeMultiAttack(int number){
    glm::vec3 look = m_camera->getLook();
    glm::vec3 dir = glm::normalize(glm::vec3(look.x, 0, look.z));
    glm::vec3 perp = glm::vec3(dir.z, 0, -dir.x);
    for(int i = 0; i < number; i ++){
        std::shared_ptr<GameObject> bullet = getBasicAttack();
        glm::vec3 oldPosition =bullet->getComponent<TransformComponent>()->getPosition();

        glm::vec3 offset = getCircleOffset(perp, i, number) / 3.f;
        bullet->getComponent<TransformComponent>()->setPosition(oldPosition + offset);
        m_gameWorld->addObject(bullet);
    }

}

void PlayerControlComponent::makeSlowAttack(){
    auto playerAbility = m_gameObject->getComponent<PlayerAbilityComponent>();


    std::shared_ptr<GameObject> bullet = getBasicAttack();
    auto physics = bullet->getComponent<PhysicsComponent>();
    physics->setVelocity(physics->getVelocity() * .6f);

    std::shared_ptr<CollisionResponseComponent> impactResponse
            = std::make_shared<ImpactBulletCollisionResponseComponent>(m_gameWorld,
                                                                       playerAbility->getBaseDamage()*playerAbility->getNumberAttacks(),
                                                                       playerAbility->getImpactPower());
    bullet->getComponent<TransformComponent>()->setSize(.6f);
    bullet->addComponent<CollisionResponseComponent>(impactResponse);
//    auto collison = bullet->getComponent<CollisionResponseComponent>();
//    auto bulletCollision = std::dynamic_pointer_cast<BulletCollisionResponseComponent>(collison);
//    if(bulletCollision){
//        bulletCollision->setDamage(playerAbility->getBaseDamage() * 2.f);
//    }
    m_gameWorld->addObject(bullet);
}

glm::vec3 PlayerControlComponent::getCircleOffset(glm::vec3 perp, int current, int totalNumber){
    if(totalNumber == 1){
        return glm::vec3(0);
    }
    float degrees = current * 360.f/totalNumber;

    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 result = glm::cos(glm::radians(degrees))* perp + glm::sin(glm::radians(degrees)) * up;

    return result;
}


std::shared_ptr<GameObject> PlayerControlComponent::getBasicAttack(){
    auto playerAbility = m_gameObject->getComponent<PlayerAbilityComponent>();

    std::shared_ptr<GameObject> sphere = std::make_shared<GameObject>();

    std::shared_ptr<ObjectDrawComponent> drawPlayerComponent = std::make_shared<ObjectDrawComponent>();
    drawPlayerComponent->setShapeType("sphere");
    drawPlayerComponent->setMaterial("attack");
    std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>();
    glm::vec3 size = glm::vec3(.2f);
    transformComponent->setSize(size);
    transformComponent->setPosition(getAttackSpherePosition());

    std::shared_ptr<PhysicsComponent> physicsComponent = std::make_shared<PhysicsComponent>();
    physicsComponent->setGravity(false);
    physicsComponent->setVelocity(getAttackVelocity());
    std::shared_ptr<CollisionComponent> collisionComponent = std::make_shared<SphereCollisionComponent>();
    std::shared_ptr<CollisionResponseComponent> collisionResponseComponent
            = std::make_shared<BulletCollisionResponseComponent>(m_gameWorld, playerAbility->getBaseDamage());
    std::shared_ptr<ContinuousCollisionComponent> continuous = std::make_shared<ContinuousCollisionComponent>(transformComponent);

    std::shared_ptr<TimeRemoveComponent> remove = std::make_shared<TimeRemoveComponent>(m_gameWorld, 15.f);
    sphere->addComponent<TransformComponent>(transformComponent);
    sphere->addComponent<PhysicsComponent>(physicsComponent);
    sphere->addComponent<ObjectDrawComponent>(drawPlayerComponent);
    sphere->addComponent<TimeRemoveComponent>(remove);
    sphere->addComponent<CollisionComponent>(collisionComponent);
    sphere->addComponent<CollisionResponseComponent>(collisionResponseComponent);
    sphere->addComponent<ContinuousCollisionComponent>(continuous);
    return sphere;
}

void PlayerControlComponent::setCanJump(){
    m_isJumping = false;
}

