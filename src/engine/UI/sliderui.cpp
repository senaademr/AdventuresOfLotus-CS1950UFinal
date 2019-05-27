#include "sliderui.h"

#include "engine/graphics/Graphics.h"
#include "shapeui.h"
#include "engine/basics/input.h"
#include "engine/graphics/Camera.h"

SliderUI::SliderUI(glm::vec3 color, std::string material, glm::vec3 position, glm::vec3 scale)
    : m_input(Input::getGlobalInstance())
{
    m_bar = std::make_shared<ShapeUI>(color, material, "uiquad", position, scale);
    float pointer_scale = scale.y;
    pointer_scale += 0.01f;
    scale.x = pointer_scale;
    scale.y = pointer_scale;
    position.y -= scale.y/1.5f;
    m_pointer = std::make_shared<ShapeUI>(color, material, "circle", position, scale);
    std::function<void(ShapeUI& shape)> pointerCallback = [this](ShapeUI& shape){
        glm::vec3 pos = m_bar->getTransform()->getPosition();
        pos.x = m_relativePos.x+(pos.x*m_relativeDimensions.x);
        glm::vec3 scale = m_bar->getTransform()->getSize();
        glm::vec2 mousePos = this->m_input->getMousePosition();
        glm::vec2 screenSize = m_graphics->getActiveCamera()->getScreenSize();
        mousePos.x /= screenSize.x;
        glm::vec3 shapePos = shape.getTransform()->getPosition();
        mousePos.x -= m_relativePos.x;
        mousePos.x /= m_relativeDimensions.x;
        if(mousePos.x < (pos.x+0.01f)){
            mousePos.x = pos.x+0.01f;
        }
        else if(mousePos.x > (pos.x + scale.x+0.01f)){
            mousePos.x = pos.x + scale.x+0.01f;
        }
        shapePos.x = mousePos.x;
        shape.setPosition(shapePos);
    };
    m_pointer->setCallback(pointerCallback);
    m_type = SLIDER;
}

void SliderUI::draw(){
    m_bar->setRelativePosition(m_relativePos);
    m_pointer->setRelativePosition(m_relativePos);
    m_bar->setRelativeDimensions(m_relativeDimensions);
    m_pointer->setRelativeDimensions(m_relativeDimensions);
    m_bar->draw();
    m_pointer->draw();
}

void SliderUI::tick(float seconds){
    glm::vec2 mousePosition = m_input->getMousePosition();
    glm::vec2 screenSize = m_graphics->getActiveCamera()->getScreenSize();
    mousePosition.x /= screenSize.x;
    mousePosition.y /= screenSize.y;
    mousePosition.y = 1.f-mousePosition.y;
    glm::vec3 scale = m_bar->getTransform()->getSize();
    glm::vec3 pos = m_bar->getTransform()->getPosition();
    pos.y *= m_relativeDimensions.y;
    pos.x = m_relativePos.x+(pos.x*m_relativeDimensions.x);
    pos.y = m_relativePos.y + m_relativeDimensions.y-pos.y;
    if(m_input->isMouseJustPressed(Qt::LeftButton)){
        if(mousePosition.x >= pos.x &&  mousePosition.x <= (pos.x + scale.x*m_relativeDimensions.x)){
            if(mousePosition.y <= pos.y && mousePosition.y >= (pos.y - scale.y)){
                m_pressed = true;
                m_pointer->callback();
                m_callback(*this);
            }
        }
    }
    else if(m_input->isMousePressed(Qt::LeftButton) && m_pressed){
        m_pointer->callback();
        m_callback(*this);
    }
    else {
        m_pressed = false;
    }
}

void SliderUI::setCallback(std::function<void(SliderUI&)> func){
    m_callback = func;
    isInteractive = true;
}

glm::vec3 SliderUI::getPointerPosition(){
    return m_pointer->getTransform()->getPosition();
}

float SliderUI::getSliderStart(){
    return m_bar->getTransform()->getPosition().x;
}

float SliderUI::getSliderEnd(){
    return m_bar->getTransform()->getSize().x;
}
