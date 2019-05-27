#ifndef APPLICATION_H
#define APPLICATION_H

#include "engine/util/CommonIncludes.h"
#include <stack>
#include <memory>
#include <QGLWidget>
#include <QTime>
#include <QTimer>

class Graphics;
class Camera;
class Screen;
class View;
class Input;

class Application
{
public:
    Application(View* view);
    virtual ~Application();


    virtual void initializeGL();
    void paintGL();
    void tick(float seconds);

    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyRepeatEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void addScreen(std::string screenName, std::shared_ptr<Screen> screen);
    void setScreen(std::string screenName);
    std::shared_ptr<Screen> getScreen(std::string name);
    void removeScreen(std::string screenName);

//    void pushScreen(std::string name, std::shared_ptr<Screen> &screen);
//    void popScreen(std::string name);

    View* getView();

private:

    void updateActiveScreen();

    View* m_view;
    std::shared_ptr<Screen> m_activeScreen;
    //QMap<std::string, std::shared_ptr<Screen> > m_allScreens;
    std::map<std::string, std::shared_ptr<Screen>> m_screens;

    Graphics* m_graphics;

    std::shared_ptr<Input> m_input;
};


#endif // APPLICATION_H
