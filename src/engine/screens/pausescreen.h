#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "engine/screens/gamescreen.h"

class Application;

class PauseScreen : public GameScreen
{
public:
    PauseScreen(View* view, Application* application);

    // Screen interface
public:
    virtual void initializeGL();
    void onSwitch();


    void unpause();

private:
    Application* m_application;


    // Screen interface
public:
};

#endif // PAUSESCREEN_H
