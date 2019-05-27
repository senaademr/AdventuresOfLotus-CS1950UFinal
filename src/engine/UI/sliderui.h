#ifndef SLIDERUI_H
#define SLIDERUI_H

#include "uielement.h"
class ShapeUI;
class Transform;
class Input;

class SliderUI : public UIElement
{
public:
    SliderUI(glm::vec3 color, std::string material, glm::vec3 position, glm::vec3 scale);

public:
    void draw() override;
    void tick(float seconds) override;
    void setCallback(std::function<void(SliderUI&)> func);
    glm::vec3 getPointerPosition();
    float getSliderStart();
    float getSliderEnd();

private:
    std::shared_ptr<Input> m_input;
    std::shared_ptr<ShapeUI> m_bar;
    std::shared_ptr<ShapeUI> m_pointer;
    std::shared_ptr<Transform> m_transform;
    std::function<void(SliderUI&)> m_callback = [](SliderUI&){};
    bool m_pressed = false;
};

#endif // SLIDERUI_H
