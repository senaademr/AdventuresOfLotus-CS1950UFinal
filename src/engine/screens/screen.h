#ifndef SCREEN_H
#define SCREEN_H

#include "engine/util/CommonIncludes.h"

#include <QApplication>
#include <QKeyEvent>
#include <memory>

class Graphics;
class Camera;
class View;

class Screen
{
public:
    Screen(View* view);
    virtual ~Screen();

    View* getView();
    std::shared_ptr<Camera> getCamera();

    virtual void initializeGL();
    virtual void paintGL();
    virtual void tick(float seconds);

    virtual void resizeGL(int w, int h);
    virtual void onSwitch();

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyRepeatEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

protected:
    View* m_view;
    Graphics* m_graphics;
    std::shared_ptr<Camera> m_camera;


};

#endif // SCREEN_H
