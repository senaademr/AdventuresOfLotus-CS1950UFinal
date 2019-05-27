#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "engine/screens/screen.h"

class Input;
class GameWorld;

class GameScreen : public Screen
{
public:
    GameScreen(View* view);

    std::shared_ptr<GameWorld> getGameWorld();
    void initializeGL();

protected:
    std::shared_ptr<GameWorld> m_gameWorld;


private:


    void paintGL() override;
    void tick(float seconds) override;

    //void resizeGL(int w, int h);

    /*
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyRepeatEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);*/
};

#endif // GAMESCREEN_H
