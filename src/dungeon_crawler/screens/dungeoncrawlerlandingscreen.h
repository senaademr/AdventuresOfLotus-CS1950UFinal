#ifndef DUNGEONCRAWLERLANDINGSCREEN_H
#define DUNGEONCRAWLERLANDINGSCREEN_H

#include "engine/screens/gamescreen.h"

class Application;
class UIInfo;
class Input;

class DungeonCrawlerLandingScreen : public GameScreen
{
public:
    DungeonCrawlerLandingScreen(View* view, Application* application);

    void initializeGL() override;
    void onSwitch() override;
private:

    void makePlayer();
private:
    Application* m_application;

    //    void keyPressEvent(QKeyEvent *event);
    //    void mousePressEvent(QMouseEvent *event) override;
};

#endif // DUNGEONCRAWLERLANDINGSCREEN_H
