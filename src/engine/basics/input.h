#ifndef INPUT_H
#define INPUT_H

#include "engine/util/CommonIncludes.h"

#include <QSet>
#include <QApplication>
#include <QKeyEvent>

#include "engine/basics/keystate.h"


class View;

class Input : public std::enable_shared_from_this<Input>
{
public:
    Input();
    ~Input();

    static std::shared_ptr<Input> getGlobalInstance() {
        static std::shared_ptr<Input> instance = std::make_shared<Input>();
        return instance;
    }

    void keyPress(QKeyEvent *event);
    void keyRelease(QKeyEvent *event);
    bool isKeyDown(int key_id);
    bool isKeyJustPressed(int key_id);
    bool isKeyJustReleased(int key_id);

    void resizeGL(int w, int h);

    bool isMouseJustPressed(unsigned int key_id);
    bool isMousePressed(unsigned int key_id);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    int getWheelDelta();
    glm::vec2 getMouseDelta();
    glm::vec2 getMousePosition();

    void tick(float seconds);

private:
    QMap<int, KeyState> m_keyStates;
    QMap<unsigned int, KeyState> m_mouseStates;
    int m_mouseWheel;
    View* m_view;


    glm::vec2 m_mousePosition;
    glm::vec2 m_lastTickMousePosition;
    glm::vec2 m_center;

};

#endif // INPUT_H
