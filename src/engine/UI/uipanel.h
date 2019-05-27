#ifndef UIPANEL_H
#define UIPANEL_H

#include "engine/util/CommonIncludes.h"
#include <map>
#include <memory>

class UIElement;
class Button;
class Graphics;

class UIPanel
{
public:
    UIPanel();
    UIPanel(float width, float height, float xpos, float ypos);
    UIPanel(float width, float height, float xpos, float ypos, glm::vec3 color, std::string materialName);
    void draw();
    void tick(float seconds);
    void addUIElement(int priority, std::string name, std::shared_ptr<UIElement> &element);
    void callbackAll();
    void callbackOne(std::string name);

private:
    float m_width;
    float m_height;
    glm::vec3 m_pos;

    glm::vec3 m_color;
    std::string m_materialName;
    bool m_isColored = false;

    std::map<std::string,std::shared_ptr<UIElement>> m_elements;
    std::map<int, std::string> m_priority;

    Graphics* m_graphics;
};

#endif // UIPANEL_H
