#include "uipanel.h"

#include "engine/graphics/Graphics.h"
#include "uielement.h"
#include "button.h"

UIPanel::UIPanel()
    :UIPanel(1.f, 1.f, 0.f, 0.f)
{

}

UIPanel::UIPanel(float width, float height, float xpos, float ypos):
    m_width(width),
    m_height(height),
    m_pos(glm::vec3(xpos, 1.f-ypos-height, 0.f)),
    m_graphics(Graphics::getGlobalInstance())
{
}

UIPanel::UIPanel(float width, float height, float xpos, float ypos, glm::vec3 color, std::string materialName):
    m_width(width),
    m_height(height),
    m_pos(glm::vec3(xpos, 1.f-ypos-height, 0.f)),
    m_color(color),
    m_materialName(materialName),
    m_graphics(Graphics::getGlobalInstance())
{
    m_isColored = true;
    Material panelMaterial;
    panelMaterial.color = m_color;
    panelMaterial.materialName = materialName;
    m_graphics->addMaterial(materialName, panelMaterial);
}

void UIPanel::draw(){
    if(m_isColored){
        m_graphics->clearTransform();
        m_graphics->setDefaultMaterial();
        m_graphics->translate(m_pos);
        m_graphics->scale(glm::vec3(m_width, m_height, 1.f));
        m_graphics->setMaterial(m_materialName);
        m_graphics->drawShape("uiquad");
    }
    for(auto name: m_priority){
        m_elements[name.second]->draw();
    }
}

void UIPanel::tick(float seconds){
    for(auto element: m_elements){
        if(element.second->getInteractive()){
            element.second->tick(seconds);
        }
    }
}

void UIPanel::addUIElement(int priority, std::string name, std::shared_ptr<UIElement> &element){
    element->setRelativePosition(m_pos);
    element->setRelativeDimensions(glm::vec2(m_width, m_height));
    m_elements.insert(std::pair<std::string,std::shared_ptr<UIElement>> (name, element));
    m_priority.insert(std::pair<int, std::string>(priority, name));
}

void UIPanel::callbackAll(){
    for(auto element: m_elements){
        if(element.second->getInteractive()){
            element.second->callback();
        }
    }
}

void UIPanel::callbackOne(std::string name){
    if(m_elements.find(name) != m_elements.end()){
        if(m_elements[name]->getInteractive()){
            m_elements[name]->callback();
        }
    }
}
