#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "engine/screens/gamescreen.h"

class Application;
class GameObject;
class TransformComponent;
class NavigationMesh;
class AnimationComponent;

class MainScreen : public GameScreen
{
public:
    MainScreen(View* view, Application* application);

    void setColor(glm::vec3 color);


private:
    void makeCylinder();
    void makeSphere();

    std::shared_ptr<GameObject> makePlayer();
    void makePlayerAnimations(std::shared_ptr<AnimationComponent> &playerAnim);

    void makeUI(std::shared_ptr<GameObject> &player);
//    float getAttackFrameSpeed(float attackSpeed, float numberOfFrames);


    // Screen interface
public:
    void initializeGL();
    void onSwitch();

private:
    Application* m_application;
    glm::vec3 m_playerColor = glm::vec3(1.f, 0.f, 0.f);
};

#endif // MAINSCREEN_H
