#include "input.h"

#include <QSet>
#include "view.h"

Input::Input() :
    m_mouseStates(QMap<unsigned int, KeyState>()),
    m_mouseWheel(0),
    m_mousePosition(glm::vec2 (0, 0)),
    m_lastTickMousePosition(glm::vec2(400,300)),
    m_center(glm::vec2(400, 300))
{

}
Input::~Input(){

}

void Input::keyPress(QKeyEvent *event){
    int key_id = event->key();
    m_keyStates.insert(key_id, KeyState::JUST_PRESSED);
}
void Input::keyRelease(QKeyEvent *event){
    int key_id = event->key();
    m_keyStates.insert(key_id, KeyState::JUST_RELEASED);

}
bool Input::isKeyDown(int key_id){
    if(!m_keyStates.contains(key_id)){
        return false;
    }
    KeyState keyState = m_keyStates.value(key_id);
    return (keyState == KeyState::PRESSED || keyState == KeyState::JUST_PRESSED);
}

bool Input::isKeyJustPressed(int key_id){
    if(!m_keyStates.contains(key_id)){
        return false;
    }
    return m_keyStates.value(key_id) == KeyState::JUST_PRESSED;
}


bool Input::isMouseJustPressed(unsigned int key_id){
    if(!m_mouseStates.contains(key_id)){
        return false;
    }
    return m_mouseStates.value(key_id) == KeyState::JUST_PRESSED;
}

bool Input::isMousePressed(unsigned int key_id){
    if(!m_mouseStates.contains(key_id)){
        return false;
    }
    auto mouseState = m_mouseStates.value(key_id);
    return (mouseState == KeyState::JUST_PRESSED) || (mouseState == KeyState::PRESSED);
}

bool Input::isKeyJustReleased(int key_id){
    if(!m_keyStates.contains(key_id)){
        return false;
    }
    return m_keyStates.value(key_id) == KeyState::JUST_RELEASED;
}

void Input::tick(float seconds){
    //std::cout << m_mouseWheel << std::endl;

    /*QMap<KeyState, std::string> keyStates;
    keyStates.insert(KeyState::JUST_PRESSED, "JUST_PRESSED");
    keyStates.insert(KeyState::PRESSED, "PRESSED");
    keyStates.insert(KeyState::JUST_RELEASED, "JUST_RELEASED");

    QMap<int, KeyState>::iterator i;
    for (i = m_keyStates.begin(); i != m_keyStates.end(); ++i){
        std::cout << i.key() << " : " << keyStates[i.value()] << std::endl;
    }*/

    //update keyStates
    QMap<int, KeyState>::iterator i;
    for (i = m_keyStates.begin(); i != m_keyStates.end(); ++i){
        if(i.value() == KeyState::JUST_PRESSED){
            m_keyStates.insert(i.key(), KeyState::PRESSED);
        }
        else if(i.value() == KeyState::JUST_RELEASED){
            m_keyStates.insert(i.key(), KeyState::RELEASED);
        }
        //std::cout << i.key() << ": " << i.value() << endl;
    }
    //update mouseStates
    QMap<unsigned int, KeyState>::iterator j;
    for (j = m_mouseStates.begin(); j != m_mouseStates.end(); ++j){
        if(j.value() == KeyState::JUST_PRESSED){
            m_mouseStates.insert(j.key(), KeyState::PRESSED);
        }
        else if(j.value() == KeyState::JUST_RELEASED){
            m_keyStates.insert(j.key(), KeyState::RELEASED);
        }
    }

    m_mouseWheel = 0;
    m_lastTickMousePosition = m_center;
}


void Input::resizeGL(int w, int h){
    m_center = glm::vec2(w/2, h/2);
}

void Input::mousePressEvent(QMouseEvent *event){
    m_mouseStates.insert(event->button(), KeyState::JUST_PRESSED);

}
void Input::mouseMoveEvent(QMouseEvent *event){
    //std::cout << event->x() << ", " << event->y() << std::endl;
    glm::vec2 newMousePosition = glm::vec2(event->x(), event->y());
//    m_lastTickMousePosition += (newMousePosition- m_center);
    //std::cout << m_lastTickMousePosition.x << ", " << m_lastTickMousePosition.y << std::endl;
    m_lastTickMousePosition = newMousePosition;

    m_mousePosition = newMousePosition;
}
void Input::mouseReleaseEvent(QMouseEvent *event){
    m_mouseStates.insert(event->button(), KeyState::JUST_RELEASED);

}
void Input::wheelEvent(QWheelEvent *event){
    m_mouseWheel = event->angleDelta().y();
}

int Input::getWheelDelta(){
    return m_mouseWheel;
}


glm::vec2 Input::getMouseDelta(){
    return m_lastTickMousePosition- m_center;
}

glm::vec2 Input::getMousePosition(){
    return m_mousePosition;
}
