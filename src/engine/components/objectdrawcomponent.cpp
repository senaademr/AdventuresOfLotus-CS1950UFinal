#include "objectdrawcomponent.h"

#include "engine/graphics/Graphics.h"
#include "engine/components/transformcomponent.h"
#include "engine/basics/gameobject.h"
#include "engine/graphics/cullers/culler.h"
#include "engine/graphics/Camera.h"

ObjectDrawComponent::ObjectDrawComponent() :
    Component(),
    Drawable(),
    m_material(""),
    m_translation(glm::vec3(0,0,0)),
    m_shapeType("cylinder"),
    m_culler(nullptr)
{

}

void ObjectDrawComponent::draw(){
    Graphics* graphics = getGraphics();
    graphics->clearTransform();
    std::shared_ptr<GameObject> gameObject = getGameObject();

    glm::vec3 graphicsPos = glm::vec3(0,0,0);
    glm::vec3 scale = glm::vec3(1, 1, 1);
    if(gameObject->hasComponent<TransformComponent>()){
        std::shared_ptr<TransformComponent> transformComponent =
                getGameObject()->getComponent<TransformComponent>();
        if(transformComponent){
            graphicsPos += transformComponent->getPosition();
            scale = transformComponent->getSize();
        }
    }
    else{
        std::cout << "No position component!" << std::endl;
    }
    //graphicsPos += getTranslation();
    graphics->translate(graphicsPos);

    graphics->scale(scale);
    graphics->setMaterial(getMaterial());
    if(m_shapeType.compare("shape") == 0){
        //draw using shape
        if(m_shape == nullptr){
            std::cout << "cannot draw shape: undefined";
        }
        else{
            graphics->drawShape(m_shape);
        }
    }
    else{
        graphics->drawShape(m_shapeType);

    }
//    glm::vec2 screenSize = m_graphics->getActiveCamera()->getScreenSize();
//    m_graphics->getActiveCamera()->setScreenSize(screenSize);
//    m_graphics->getActiveCamera()->setUI(true);
//    m_graphics->setCamera(m_graphics->getActiveCamera());
//    m_graphics->clearTransform();
//    m_graphics->setDefaultMaterial();
//    m_graphics->translate(glm::vec3(100.f, 350.f, 0)); // you need to come up with a position
//    m_graphics->drawText("Press any key to start", 80); // fill this in with text and a text size
//    m_graphics->getActiveCamera()->setUI(false);
//    m_graphics->getActiveCamera()->setScreenSize(screenSize);
//    m_graphics->setCamera(m_graphics->getActiveCamera());
}

void ObjectDrawComponent::setCuller(std::shared_ptr<Culler> culler){
    m_culler = culler;
}

bool ObjectDrawComponent::shouldCull(QList<glm::vec4> &planes){
    if(m_culler == nullptr){
        return false;
    }
    return m_culler->shouldCull(planes);
}

std::string ObjectDrawComponent::getMaterial(){
    return m_material;
}
void ObjectDrawComponent::setMaterial(std::string material){
    m_material = material;
}


glm::vec3 ObjectDrawComponent::getTranslation(){
    return m_translation;
}
void ObjectDrawComponent::setTranslation(glm::vec3 translation){
    m_translation = translation;
}

std::string ObjectDrawComponent::getShapeType(){
    return m_shapeType;
}
void ObjectDrawComponent::setShapeType(std::string newShape){
    m_shapeType = newShape;
}


void ObjectDrawComponent::setShape(std::shared_ptr<Shape> shape){
    m_shape = shape;
}
