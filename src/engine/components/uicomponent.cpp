#include "uicomponent.h"

#include "engine/graphics/Camera.h"
#include "engine/graphics/Graphics.h"
#include "engine/basics/gameobject.h"
#include "engine/UI/uielement.h"
#include "engine/components/transformcomponent.h"
#include "engine/UI/button.h"

#include "engine/UI/uipanel.h"

UIComponent::UIComponent()
    : Component(),
      Drawable(),
      Tickable(),
      m_graphics(Graphics::getGlobalInstance())
{
}

void UIComponent::addPanel(std::string name, std::shared_ptr<UIPanel> panel){
    m_panels.insert(std::pair<std::string,std::shared_ptr<UIPanel>>(name,panel));
}

std::shared_ptr<UIPanel> UIComponent::getPanel(std::string name){
    if(m_panels.find(name) != m_panels.end()){
        return m_panels[name];
    }
    return nullptr;
}

void UIComponent::draw(){
    setUp();
    for(auto panel: m_panels){
        panel.second->draw();
    }
    cleanUp();
}

void UIComponent::tick(float seconds){
    for(auto panel : m_panels){
        panel.second->tick(seconds);
    }
}


void UIComponent::setUp(){
    m_screensize = m_graphics->getActiveCamera()->getScreenSize();
    m_graphics->getActiveCamera()->setScreenSize(glm::vec2(1));
    m_graphics->getActiveCamera()->setUI(true);
    m_graphics->setCamera(m_graphics->getActiveCamera());
}

void UIComponent::cleanUp(){
    m_graphics->getActiveCamera()->setUI(false);
    m_graphics->getActiveCamera()->setScreenSize(m_screensize);
    m_graphics->setCamera(m_graphics->getActiveCamera());
}

