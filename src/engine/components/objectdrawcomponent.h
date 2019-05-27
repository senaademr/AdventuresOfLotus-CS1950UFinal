#ifndef OBJECTDRAWCOMPONENT_H
#define OBJECTDRAWCOMPONENT_H

#include "drawable.h"
#include "component.h"
#include <QList>

class Shape;
class Culler;

class ObjectDrawComponent : public Component, public Drawable
{
public:
    ObjectDrawComponent();

    virtual void draw() override;

    std::string getMaterial();
    void setMaterial(std::string material);

    glm::vec3 getTranslation();
    void setTranslation(glm::vec3 translation);

    std::string getShapeType();
    void setShapeType(std::string newShape);

    void setShape(std::shared_ptr<Shape> shape);

    void setCuller(std::shared_ptr<Culler> culler);
    bool shouldCull(QList<glm::vec4> &planes);


private:
    std::string m_material;
    glm::vec3 m_translation;
    std::string m_shapeType;
    std::shared_ptr<Shape> m_shape;
    std::shared_ptr<Culler> m_culler;
};

#endif // OBJECTDRAWCOMPONENT_H
