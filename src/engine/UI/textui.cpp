#include "textui.h"

#include "engine/graphics/Graphics.h"
#include "engine/util/transform.h"
#include "engine/graphics/Font.h"
#include "engine/util/util.h"

TextUI::TextUI(std::string text, float textSize, glm::vec3 color, glm::vec3 pos, glm::vec3 scale, float angle, glm::vec3 rotation)
    : m_text(text),
      m_textSize(textSize),
      m_color(color),
      m_transform(nullptr)
{
    m_transform = std::make_shared<Transform>(pos, scale, angle, rotation);
    m_type = TEXT;
}

TextUI::TextUI(std::string text, float textSize, glm::vec3 color, glm::vec3 pos, glm::vec3 scale)
    : TextUI(text, textSize, color, pos, scale, 0.f, glm::vec3(0.f))
{

}

TextUI::TextUI(std::string text, float textSize, glm::vec3 color, glm::vec3 pos)
    : TextUI(text, textSize, color, pos, glm::vec3(1.f), 0.f, glm::vec3(0.f))
{

}

void TextUI::draw(){
    m_graphics->clearTransform();
    m_graphics->setDefaultMaterial();
    glm::vec3 scale = m_transform->getSize();
    scale.x *= m_relativeDimensions.x;
    scale.y *= m_relativeDimensions.y;
    glm::vec3 pos = m_transform->getPosition();
    pos.y *= m_relativeDimensions.y;
    m_graphics->translate(glm::vec3(m_relativePos.x+(pos.x*m_relativeDimensions.x), m_relativePos.y+m_relativeDimensions.y-(pos.y), m_relativePos.z+pos.z));
    if(m_transform->getAngle() != 0.f && (m_transform->getRotationAxis().x != 0.f || m_transform->getRotationAxis().y != 0.f || m_transform->getRotationAxis().z != 0.f)){
         m_graphics->rotate(m_transform->getAngle(), m_transform->getRotationAxis());
    }
    m_graphics->scale(m_transform->getSize());
    m_graphics->setColor(m_color);
    m_graphics->drawText(m_fontName, m_text, m_textSize);
}

void TextUI::tick(float seconds){
}

glm::vec3 TextUI::getAlignmentTransform(){


    FontMetrics metrics = m_graphics->getFontMetrics(m_fontName, m_text, m_textSize);
    glm::vec3 size = m_transform->getSize();

    float xDisplacement = 0;
    float yDisplacement = 0;

    float xDisplacementLeft = 0;
    float xDisplacementCenter = (size.x - metrics.width)/2.f;
    float xDisplacementRight = size.x - metrics.width;

    float yDisplacementTop = size.y-metrics.ascent;
    float yDisplacementCenter =(size.y-metrics.ascent)/2.f;
    float yDispacementBottom = - metrics.descent;

    switch(m_alignment){
        case(TextAlignment::NONE):
            return glm::vec3(0);

        case(TextAlignment::TOP_LEFT):
            xDisplacement = xDisplacementLeft;
            yDisplacement = yDisplacementTop;
            break;

        case(TextAlignment::TOP_CENTER):
            xDisplacement = xDisplacementCenter;
            yDisplacement = yDisplacementTop;
            break;

        case(TextAlignment::TOP_RIGHT):
            xDisplacement = xDisplacementRight;
            yDisplacement = yDisplacementTop;
            break;

        case(TextAlignment::CENTER_LEFT):
            xDisplacement = xDisplacementLeft;
            yDisplacement = yDisplacementCenter;
            break;

        case(TextAlignment::CENTER_CENTER):
            xDisplacement = xDisplacementCenter;
            yDisplacement = yDisplacementCenter;
            break;

        case(TextAlignment::CENTER_RIGHT):
            xDisplacement = xDisplacementRight;
            yDisplacement = yDisplacementCenter;
            break;

        case(TextAlignment::BOTTOM_LEFT):
            xDisplacement = xDisplacementLeft;
            yDisplacement = yDispacementBottom;
            break;

        case(TextAlignment::BOTTOM_CENTER):
            xDisplacement = xDisplacementCenter;
            yDisplacement = yDispacementBottom;
            break;

        case(TextAlignment::BOTTOM_RIGHT):
            xDisplacement = xDisplacementRight;
            yDisplacement = yDispacementBottom;
            break;
    }

    return glm::vec3(xDisplacement, yDisplacement, 0);
}


void TextUI::setAlignment(TextAlignment alignment){
    m_alignment = alignment;
}

void TextUI::setText(std::string newText){
    m_text = newText;
}

void TextUI::setCallback(std::function<void (TextUI &)> func){
    m_callback = func;
    isInteractive = true;
}

void TextUI::callback(){
    m_callback(*this);
}
