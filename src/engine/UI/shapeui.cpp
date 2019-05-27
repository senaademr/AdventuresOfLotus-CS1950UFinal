#include "shapeui.h"

#include "engine/graphics/Graphics.h"
#include "engine/graphics/Shape.h"
#include "engine/graphics/Camera.h"

ShapeUI::ShapeUI(glm::vec3 color, std::string material, std::string shape, glm::vec3 position)
    : ShapeUI(color, material, shape, position, glm::vec3(1.f), 0.f, glm::vec3(0.f))
{
}

ShapeUI::ShapeUI(glm::vec3 color, std::string material, std::string shape, glm::vec3 position, glm::vec3 scale, float angle, glm::vec3 rotation)
    : m_initialSize(scale),
      m_transform(nullptr),
      m_material(material)
{
    m_transform = std::make_shared<Transform>(position, scale, angle, rotation);
    m_shape = std::make_shared<Shape>(shape);
    Material shapeMaterial;
    shapeMaterial.color = color;
    shapeMaterial.materialName = material;
    m_graphics->addMaterial(material, shapeMaterial);
    m_type = SHAPE;
}


ShapeUI::ShapeUI(glm::vec3 color, std::string material, std::string shape, glm::vec3 position, glm::vec3 scale)
    : ShapeUI(color, material, shape, position, scale, 0.f, glm::vec3(0.f))
{

}

ShapeUI::ShapeUI(std::string texture, std::string material, std::string shape, glm::vec3 position)
    : ShapeUI(texture, material, shape, position, glm::vec3(1.f), 0.f, glm::vec3(0.f))
{
}

ShapeUI::ShapeUI(std::string texture, std::string material, std::string shape, glm::vec3 position, glm::vec3 scale)
    : ShapeUI(texture, material, shape, position, scale, 0.f, glm::vec3(0.f))
{
}

ShapeUI::ShapeUI(std::string texture, std::string material, std::string shape, glm::vec3 position, glm::vec3 scale, float angle, glm::vec3 rotation)
    : m_initialSize(scale),
      m_transform(nullptr),
      m_material(material)
{
    m_transform = std::make_shared<Transform>(position, scale, angle, rotation);
    m_shape = std::make_shared<Shape>(shape);
    Material shapeMaterial;
    shapeMaterial.textureName = texture;
    shapeMaterial.materialName = material;
    m_graphics->addMaterial(material, shapeMaterial);
    m_type = SHAPE;
}

std::shared_ptr<Transform> ShapeUI::getTransform(){
    return m_transform;
}

void ShapeUI::setScaleX(float scale){
    glm::vec3 currentScale = m_transform->getSize();
    currentScale.x = scale*m_initialSize.x;
    Transform newTransform = m_transform->setSize(currentScale);
    m_transform = std::make_shared<Transform>(newTransform);
}

void ShapeUI::setScaleY(float scale){
    glm::vec3 currentScale = m_transform->getSize();
    currentScale.y *= scale;
    m_transform->setSize(currentScale);
}

void ShapeUI::setPosition(glm::vec3 pos){
    Transform newTransform = m_transform->setPosition(pos);
    m_transform = std::make_shared<Transform>(newTransform);
}

void ShapeUI::draw(){
    if(isOrthographic){
        m_graphics->clearTransform();
        m_graphics->setDefaultMaterial();
        glm::vec3 scale = m_transform->getSize();
        glm::vec3 pos = convertToScreenSpace();
        m_graphics->translate(glm::vec3(pos.x, 1.f-pos.y, pos.z));
        if(m_transform->getAngle() != 0.f && (m_transform->getRotationAxis().x != 0.f || m_transform->getRotationAxis().y != 0.f || m_transform->getRotationAxis().z != 0.f)){
             m_graphics->rotate(m_transform->getAngle(), m_transform->getRotationAxis());
        }
        m_graphics->scale(scale);
        m_graphics->setMaterial(m_material);
        if(pos.z > 0){
            m_graphics->drawShape(m_shape);
        }
    }else{
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
        m_graphics->scale(scale);
        m_graphics->setMaterial(m_material);
        m_graphics->drawShape(m_shape);
    }
}

void ShapeUI::tick(float seconds){
    if(isOrthographic){
        callback();
    }
}

void ShapeUI::setCallback(std::function<void(ShapeUI& shape)> func){
    m_callback = func;
    isInteractive = true;
}

void ShapeUI::callback(){
    m_callback(*this);
}

glm::vec3 ShapeUI::convertToScreenSpace(){
    glm::vec4 position = glm::vec4(m_transform->getPosition(), 1.f);
    glm::mat4x4 proj = m_graphics->getActiveCamera()->getProjection();
    glm::mat4x4 view = m_graphics->getActiveCamera()->getView();
    position = proj*view*position;
    glm::vec3 clip = glm::vec3(position.x/position.w, position.y/ position.w, position.z/position.w);
    clip.x = (clip.x+1.f)*0.5f*m_graphics->getActiveCamera()->getScreenSize().x;
    clip.y = (1.f-clip.y)*0.5f*m_graphics->getActiveCamera()->getScreenSize().y;
    return clip;
}
