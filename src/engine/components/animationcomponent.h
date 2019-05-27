#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "component.h"
#include "tickable.h"
#include "drawable.h"
#include "engine/Animation/mesh.h"

class AnimationComponent : public Component, public Tickable, public Drawable
{
public:
    AnimationComponent();
    AnimationComponent(std::string filename, std::string material);
    AnimationComponent(std::string filename, glm::vec3 axis, float angle, std::string material);
    AnimationComponent(std::shared_ptr<Mesh> &mesh, std::string material);
    AnimationComponent(std::shared_ptr<Mesh> &mesh, glm::vec3 axis, float angle, std::string material);

    static float getAttackFrameSpeed(float attackSpeed, float numberOfFrames);


    void tick(float seconds) override;
    void draw() override;

    void changeAnimation(int i);
    void add(std::string name, float speed, float duration, float offset, float repeat);
    void update(int index, float speed, int repeat);
    void changeCurrentAnimation(std::string name);

    void setDrawScale(float scale);
    void setDrawScale(glm::vec3 scale);
    glm::vec3 getDrawScale();

private:
    std::shared_ptr<Mesh> m_mesh;
    std::vector<aiMatrix4x4> m_transforms;
    glm::mat4 aiMatToGlm(aiMatrix4x4);
    float m_count = 0.f;
    glm::vec3 m_initialRotationAxis = glm::vec3(0.f);
    float m_initialAngle = 0.f;
    std::string m_material;
    glm::vec3 m_drawScale = glm::vec3(1);
};

#endif // ANIMATIONCOMPONENT_H
