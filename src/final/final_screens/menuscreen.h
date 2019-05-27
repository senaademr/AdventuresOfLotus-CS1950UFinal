#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "engine/screens/gamescreen.h"

class Application;

class MenuScreen: public GameScreen
{
public:
    MenuScreen(View* view, Application* application);

    void initializeGL() override;
    void onSwitch() override;

    void makePlayer();

    void keyPressEvent(QKeyEvent *event) override;
private:
    Application* m_application;
    glm::vec3 m_playerColor= glm::vec3(1.f, 0.f, 0.f);

};
#endif // MENUSCREEN_H
