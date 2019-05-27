#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include "drawable.h"
#include "tickable.h"
#include "component.h"
#include <map>

class UIElement;
class Button;
class UIPanel;

class  UIComponent : public Component, public Drawable, public Tickable
{
public:
    UIComponent();

    void addPanel(std::string name, std::shared_ptr<UIPanel> panel);
    std::shared_ptr<UIPanel> getPanel(std::string name);

    // Drawable interface
    void draw() override;

    // Tickable interface
    void tick(float seconds) override;

private:
    void setUp();
    void cleanUp();
    glm::vec3 getPosition();

private:
    std::map<std::string, std::shared_ptr<UIPanel>> m_panels;
    Graphics* m_graphics;
    glm::vec2 m_screensize;
};

#endif // UICOMPONENT_H
