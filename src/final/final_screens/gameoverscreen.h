#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "engine/screens/gamescreen.h"
class Application;

class GameOverScreen: public GameScreen
{
public:
    GameOverScreen(View* view, Application* application);

    void initializeGL() override;
    void onSwitch() override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    Application* m_application;
};

#endif // GAMEOVERSCREEN_H
