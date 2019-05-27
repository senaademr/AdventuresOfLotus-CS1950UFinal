#ifndef SHAPEUI_H
#define SHAPEUI_H

#include "engine/util/CommonIncludes.h"
#include "uielement.h"
#include "engine/util/transform.h"

class Shape;

class ShapeUI : public UIElement
{
public:
    ShapeUI(glm::vec3 color, std::string material, std::string shape, glm::vec3 position);
    ShapeUI(glm::vec3 color, std::string material, std::string shape, glm::vec3 position, glm::vec3 scale);
    ShapeUI(glm::vec3 color, std::string material, std::string shape, glm::vec3 position, glm::vec3 scale, float angle, glm::vec3 rotation);
    ShapeUI(std::string textureName, std::string material, std::string shape, glm::vec3 position);
    ShapeUI(std::string textureName, std::string material, std::string shape, glm::vec3 position, glm::vec3 scale);
    ShapeUI(std::string textureName, std::string material, std::string shape, glm::vec3 position, glm::vec3 scale, float angle, glm::vec3 rotation);

public:
    void draw() override;
    void tick(float seconds) override;

    std::shared_ptr<Transform> getTransform();
    void setScaleX(float scaleX);
    void setScaleY(float scaleY);
    void setPosition(glm::vec3 pos);

    void setCallback(std::function<void(ShapeUI &)> func);
    void callback() override;

private:
    glm::vec3 m_initialSize;
    std::shared_ptr<Transform> m_transform;
    std::string m_material = "default";
    std::shared_ptr<Shape> m_shape;
    std::function<void(ShapeUI&)> m_callback = [](ShapeUI&) {};

    glm::vec3 convertToScreenSpace();
};

#endif // SHAPEUI_H
