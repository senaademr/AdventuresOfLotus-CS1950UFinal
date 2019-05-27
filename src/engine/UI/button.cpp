#include "button.h"

#include "engine/basics/input.h"
#include "engine/util/util.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Shape.h"
#include "engine/graphics/Camera.h"

Button::Button(std::string text, float textSize, glm::vec3 color, std::string materialName, std::string shape, glm::vec3 pos,
               glm::vec3 scale, glm::vec3 rot, float angle)
    : m_input(Input::getGlobalInstance()),
      m_text(text),
      m_textSize(textSize),
      m_material(materialName),
      m_transform(nullptr)
{
    m_transform = std::make_shared<Transform>(pos, scale, angle, rot);
    m_shape = std::make_shared<Shape>(shape);
    Material shapeMaterial;
    shapeMaterial.color = color;
    shapeMaterial.materialName = materialName;
    m_graphics->addMaterial(materialName, shapeMaterial);
    m_type = BUTTON;
}

Button::Button(std::string text, float textSize, glm::vec3 color, std::string materialName, std::string shape, glm::vec3 pos,
               glm::vec3 scale)
    : Button(text, textSize, color, materialName, shape, pos,
             scale, glm::vec3(0.f), 0.f)
{

}

Button::Button(std::string text, float textSize, glm::vec3 color, std::string materialName, std::string shape, glm::vec3 pos)
    : Button(text, textSize, color, materialName, shape, pos,
             glm::vec3(1.f), glm::vec3(0.f), 0.f)
{

}

void Button::tick(float seconds){
    if(m_input->isMouseJustPressed(Qt::LeftButton)){
        glm::vec2 mousePosition = m_input->getMousePosition();
        glm::vec2 screenSize = m_graphics->getActiveCamera()->getScreenSize();
        mousePosition.x /= screenSize.x;
        mousePosition.y /= screenSize.y;
        mousePosition.y = 1.f-mousePosition.y;
        glm::vec3 scale = m_transform->getSize();
        glm::vec3 pos = m_transform->getPosition();
        pos.y *= m_relativeDimensions.y;
        pos.x = m_relativePos.x+(pos.x*m_relativeDimensions.x);
        pos.y = m_relativePos.y + m_relativeDimensions.y-pos.y;
        if(mousePosition.x >= pos.x &&  mousePosition.x <= (pos.x + scale.x)){
            if(mousePosition.y <= pos.y && mousePosition.y >= (pos.y - scale.y)){
                m_callback(*this);
            }
        }
    }
}

void Button::draw(){
    m_graphics->clearTransform();
    m_graphics->setDefaultMaterial();
    glm::vec3 scale = m_transform->getSize();
    scale.x *= m_relativeDimensions.x;
    scale.y *= m_relativeDimensions.y;
    glm::vec3 pos = m_transform->getPosition();
    pos.y *= m_relativeDimensions.y;
    pos.y += scale.y;
    m_graphics->translate(glm::vec3(m_relativePos.x+(pos.x*m_relativeDimensions.x), m_relativePos.y+m_relativeDimensions.y-(pos.y), m_relativePos.z+pos.z));
    if(m_transform->getAngle() != 0.f && (m_transform->getRotationAxis().x != 0.f || m_transform->getRotationAxis().y != 0.f || m_transform->getRotationAxis().z != 0.f)){
         m_graphics->rotate(m_transform->getAngle(), m_transform->getRotationAxis());
    }
    m_graphics->scale(m_transform->getSize());
    m_graphics->setMaterial(m_material);
    m_graphics->drawShape(m_shape);
    m_graphics->setDefaultMaterial();
    m_graphics->drawText("default", m_text, m_textSize);
}

void Button::callback(){
    m_callback(*this);
}

void Button::setCallback(std::function<void (Button &)> func){
    m_callback = func;
    isInteractive = true;
}
