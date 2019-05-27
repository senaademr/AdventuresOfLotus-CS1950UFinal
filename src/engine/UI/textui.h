#ifndef TEXTUI_H
#define TEXTUI_H

#include "uielement.h"
#include "engine/util/CommonIncludes.h"
#include "textalignment.h"

#include <QMap>
class Transform;
struct FontMetrics;

class TextUI : public UIElement
{
public:
    TextUI(std::string text, float textSize, glm::vec3 color, glm::vec3 pos);
    TextUI(std::string text, float textSize, glm::vec3 color, glm::vec3 pos, glm::vec3 scale);
    TextUI(std::string text, float textSize, glm::vec3 color, glm::vec3 pos, glm::vec3 scale, float angle, glm::vec3 rotation);

    // UIElement interface

public:
    void draw() override;
    void tick(float seconds) override;

    void setAlignment(TextAlignment alignment);
    void setText(std::string newText);
    void setCallback(std::function<void(TextUI &)> func);
    void callback() override;


private:

    glm::vec3 getAlignmentTransform();

private:
    std::string m_text = "";
    float m_textSize = 0.1f;
    glm::vec3 m_color = glm::vec3(1);
    std::shared_ptr<Transform> m_transform;
    std::string m_fontName = "default";
    TextAlignment m_alignment = TextAlignment::NONE;
    std::function<void(TextUI&)> m_callback = [](TextUI&) {};
};

#endif // TEXTUI_H
