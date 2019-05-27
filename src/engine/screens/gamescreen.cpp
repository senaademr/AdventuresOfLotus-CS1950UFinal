#include "gamescreen.h"

#include "engine/basics/gameworld.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"

GameScreen::GameScreen(View* view) :
    Screen(view),
    m_gameWorld(nullptr)
{
    assert(m_camera);
    m_gameWorld = std::make_shared<GameWorld>(m_camera);
}

std::shared_ptr<GameWorld> GameScreen::getGameWorld(){
    return m_gameWorld;
}

void GameScreen::initializeGL(){}
void GameScreen::paintGL(){

    m_gameWorld->paintGL();
}
void GameScreen::tick(float seconds){
    m_gameWorld->tick(seconds);
}

//void GameScreen::resizeGL(int w, int h){}

/*
void GameScreen::mousePressEvent(QMouseEvent *event){}
void GameScreen::mouseMoveEvent(QMouseEvent *event){}
void GameScreen::mouseReleaseEvent(QMouseEvent *event){}
void GameScreen::wheelEvent(QWheelEvent *event){}

void GameScreen::keyPressEvent(QKeyEvent *event){}

void GameScreen::keyRepeatEvent(QKeyEvent *event){}
void GameScreen::keyReleaseEvent(QKeyEvent *event){}*/
