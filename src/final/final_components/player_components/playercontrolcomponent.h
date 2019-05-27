#ifndef PLAYERCONTROLCOMPONENT_H
#define PLAYERCONTROLCOMPONENT_H

#include "engine/components/component.h"
#include "engine/components/tickable.h"

class Camera;
class Input;
class ValueNoise;
class GameWorld;
class TickTimer;

class PlayerControlComponent : public Component, public Tickable
{
public:
    PlayerControlComponent(std::shared_ptr<Camera> camera, std::shared_ptr<GameWorld> gameWorld);

    // Tickable interface
public:
    void tick(float seconds) override;

    void updateAttackTimer();
    void setCanJump();

private:
    bool handleMovement(float seconds);
    void handleAttackSwitch();
    void handleJump();
    void handleMeditation(float seconds);


    glm::vec3 getCircleOffset(glm::vec3 perp, int current, int totalNumber);
    std::shared_ptr<GameObject> getBasicAttack();
    void makeMultiAttack(int number);
    void makeSlowAttack();
    void makeAttack();
    glm::vec3 getAttackSpherePosition();
    glm::vec3 getAttackVelocity();

    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<GameWorld> m_gameWorld;
    std::shared_ptr<TickTimer> m_attackTimer;
    std::shared_ptr<Input> m_input;

//    float m_velocity = 7.f;
    float m_jumpVelocity = 10.f;
    float m_bulletVelocity = 20.f;

    bool m_isJumping = false;
    bool m_isMeditating = false;
    bool m_isSprinting = false;

    int m_deathCount = 0;
};

#endif // PLAYERCONTROLCOMPONENT_H
