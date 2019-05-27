#ifndef BUTTON_H
#define BUTTON_H

#include "engine/util/CommonIncludes.h"
#include "uielement.h"
#include <functional>
#include "engine/util/transform.h"

class Input;
class Shape;


class Button : public UIElement
{
public:
    Button(std::string text, float size, glm::vec3 color, std::string materialName, std::string shape, glm::vec3 pos);
    Button(std::string text, float size, glm::vec3 color, std::string materialName, std::string shape, glm::vec3 pos,
                   glm::vec3 scale);
    Button(std::string text, float size, glm::vec3 color, std::string materialName, std::string shape, glm::vec3 pos,
                   glm::vec3 scale, glm::vec3 rot, float angle);

    void tick(float seconds) override;
    void draw() override;

    void setCallback(std::function<void(Button&)> func);
    void callback() override;

private:

    std::shared_ptr<Input> m_input;
    std::string m_text;
    float m_textSize;
    std::string m_material = "default";
    std::shared_ptr<Shape> m_shape;
    std::shared_ptr<Transform> m_transform;
    std::function<void(Button&)> m_callback = [](Button&){};
};

#endif // BUTTON_H
