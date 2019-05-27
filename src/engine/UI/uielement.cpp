#include "uielement.h"

#include "engine/graphics/Graphics.h"

UIElement::UIElement()
    : m_graphics(Graphics::getGlobalInstance()),
      m_type(NONE)
{
}

UIElement::~UIElement(){

}

void UIElement::draw(){

}

void UIElement::tick(float seconds){
}

void UIElement::setRelativePosition(glm::vec3 pos){
    m_relativePos = pos;
}

void UIElement::setRelativeDimensions(glm::vec2 dim){
    m_relativeDimensions = dim;
}

void UIElement::setOrthographic(bool ortho){
    isOrthographic = ortho;
}

bool UIElement::getOrthographic(){
    return isOrthographic;
}

void UIElement::setInteractive(bool interact){
    isInteractive = interact;
}

bool UIElement::getInteractive(){
    return isInteractive;
}

UIType UIElement::getType(){
    return m_type;
}

void UIElement::callback(){

}
