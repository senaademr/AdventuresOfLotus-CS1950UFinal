#include "application.h"

#include "engine/graphics/GraphicsDebug.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "engine/graphics/Material.h"
#include "engine/screens/screen.h"
#include "view.h"
#include "engine/screens/blankscreen.h"
#include "engine/basics/input.h"

Application::Application(View* view) :
    m_view(view),
    m_graphics(nullptr),
    m_input(nullptr)
{
    m_graphics = Graphics::getGlobalInstance();
    m_activeScreen = std::make_shared<BlankScreen>(m_view);
    m_input = Input::getGlobalInstance();
}

Application::~Application(){
}

void Application::initializeGL(){
    m_activeScreen->initializeGL();
}
void Application::paintGL(){
    m_activeScreen->paintGL();
}

void Application::tick(float seconds){
    m_activeScreen->tick(seconds);
    m_input->tick(seconds);

}

void Application::mousePressEvent(QMouseEvent *event){
    m_input->mousePressEvent(event);
    m_activeScreen->mousePressEvent(event);
}

void Application::mouseMoveEvent(QMouseEvent *event){
    m_input->mouseMoveEvent(event);
    m_activeScreen->mouseMoveEvent(event);
}

void Application::mouseReleaseEvent(QMouseEvent *event){
    m_input->mouseReleaseEvent(event);
    m_activeScreen->mouseReleaseEvent(event);
}

void Application::wheelEvent(QWheelEvent *event){
    m_input->wheelEvent(event);
    m_activeScreen->wheelEvent(event);
}

void Application::keyPressEvent(QKeyEvent *event){
    m_input->keyPress(event);
    m_activeScreen->keyPressEvent(event);
}

void Application::keyRepeatEvent(QKeyEvent *event){
    m_activeScreen->keyRepeatEvent(event);
}

void Application::keyReleaseEvent(QKeyEvent *event){
    m_input->keyRelease(event);
    m_activeScreen->keyReleaseEvent(event);
}

void Application::resizeGL(int w, int h){
    m_input->resizeGL(w, h);
    m_activeScreen->resizeGL(w, h);
}

void Application::addScreen(std::string screenName, std::shared_ptr<Screen> screen){
    m_screens.insert(std::pair<std::string, std::shared_ptr<Screen>>(screenName, screen));
}

void Application::setScreen(std::string screenName){
    if(m_screens.find(screenName) != m_screens.end()){
        m_activeScreen = m_screens[screenName];
        m_graphics->setCamera(m_activeScreen->getCamera());
        m_activeScreen->initializeGL();
        m_activeScreen->resizeGL(m_view->width(), m_view->height());
        m_activeScreen->onSwitch();
    }
}

void Application::removeScreen(std::string screenName){
    if(m_screens.find(screenName) != m_screens.end()){
        m_screens.erase(screenName);
    }
}

std::shared_ptr<Screen> Application::getScreen(std::string screenName){
    if(m_screens.find(screenName) != m_screens.end()){
        return m_screens[screenName];
    }
    else{
        std::cout << "no screen with name: " << screenName << ". returning nullptr" << std::endl;
        return nullptr;
    }
}

//void Application::pushScreen(std::string name, std::shared_ptr<Screen> &screen)
//{
//    m_screens.push(screen);
//    updateActiveScreen();
//}

//void Application::popScreen(std::string name)
//{
//    if (m_screens.size() > 1)
//    {
//        m_screens.pop();
//        updateActiveScreen();
//    }
//}

//void Application::updateActiveScreen()
//{
//    m_activeScreen = m_screens.top();
//    m_graphics->setCamera(m_activeScreen->getCamera());
//    m_activeScreen->resizeGL(m_view->width(), m_view->height());
//    m_activeScreen->onSwitch();
//}

View* Application::getView(){
    return m_view;
}
