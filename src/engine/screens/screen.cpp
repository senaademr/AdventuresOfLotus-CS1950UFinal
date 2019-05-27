#include "screen.h"

#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include <QApplication>
#include <QKeyEvent>

#include "view.h"


Screen::Screen(View* view) :
    m_view(view),
    m_graphics(nullptr)
{
    m_graphics = Graphics::getGlobalInstance();
    m_camera = std::make_unique<Camera>();
    m_camera->setEye(glm::vec3(0, 1, 0));
    //m_graphics->setCamera(m_camera);
}

Screen::~Screen(){

}

View* Screen::getView(){
    return m_view;
}

std::shared_ptr<Camera> Screen::getCamera(){
    return m_camera;
}

void Screen::initializeGL(){}
void Screen::paintGL(){}
void Screen::tick(float seconds){}

void Screen::resizeGL(int w, int h){
    m_camera->setScreenSize(glm::vec2(w, h));
}

void Screen::onSwitch(){}
void Screen::mousePressEvent(QMouseEvent *event){}
void Screen::mouseMoveEvent(QMouseEvent *event){
    /*int deltaX = event->x() - m_view->width() / 2;
    int deltaY = event->y() - m_view->height() / 2;

    if(m_view->getCaptureMouse()) {
        if (deltaX == 0 && deltaY == 0) {
            return;
        }

        QCursor::setPos(m_view->mapToGlobal(QPoint(m_view->width() / 2, m_view->height() / 2)));
    }
    m_camera->rotate(-deltaX / 100.f, -deltaY / 100.f);*/
}
void Screen::mouseReleaseEvent(QMouseEvent *event){}
void Screen::wheelEvent(QWheelEvent *event){}
void Screen::keyPressEvent(QKeyEvent *event){}
void Screen::keyRepeatEvent(QKeyEvent *event){}
void Screen::keyReleaseEvent(QKeyEvent *event){}
