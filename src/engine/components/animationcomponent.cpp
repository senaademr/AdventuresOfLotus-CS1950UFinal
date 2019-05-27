#include "animationcomponent.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Shape.h"
#include "engine/components/transformcomponent.h"
#include "engine/basics/gameobject.h"

AnimationComponent::AnimationComponent() : Component (), Tickable (), Drawable ()
{
}

AnimationComponent::AnimationComponent(std::string filename, std::string material) : Component (), Tickable (), Drawable ()
{
    m_mesh = std::make_shared<Mesh>();
    m_mesh->loadMesh(filename);
    m_mesh->transformBones(0, m_transforms);
    m_material = material;
}

AnimationComponent::AnimationComponent(std::string filename, glm::vec3 axis, float angle, std::string material) : Component (), Tickable (), Drawable ()
{
    m_mesh = std::make_shared<Mesh>();
    m_mesh->loadMesh(filename);
    m_mesh->transformBones(0, m_transforms);
    m_initialRotationAxis = axis;
    m_initialAngle = angle;
    m_material = material;
}

AnimationComponent::AnimationComponent(std::shared_ptr<Mesh> &mesh, std::string material) : Component (), Tickable (), Drawable ()
{
    m_mesh = mesh;
    m_mesh->transformBones(0, m_transforms);
    m_material = material;
}


AnimationComponent::AnimationComponent(std::shared_ptr<Mesh> &mesh, glm::vec3 axis, float angle, std::string material) : Component (), Tickable (), Drawable ()
{
    m_mesh = mesh;
    m_mesh->transformBones(0, m_transforms);
    m_initialRotationAxis = axis;
    m_initialAngle = angle;
    m_material = material;
}

void AnimationComponent::tick(float seconds){ 
    m_mesh->transformBones(m_count, m_transforms);
    m_count += seconds* 60.f;
}

void AnimationComponent::draw(){
    Graphics* graphics = getGraphics();
    graphics->clearTransform();
    std::shared_ptr<GameObject> gameObject = getGameObject();
    std::shared_ptr<TransformComponent> transformComponent = getGameObject()->getComponent<TransformComponent>();
    graphics->translate(transformComponent->getPosition());
    std::pair<float, glm::vec3> rotation = transformComponent->getRotation();
    if(rotation.first != 0.f && (rotation.second.x != 0.f ||
                                          rotation.second.y != 0.f ||
                                          rotation.second.z != 0.f)){
         graphics->rotate(rotation.first, rotation.second);
    }
    if(m_initialAngle != 0 && (m_initialRotationAxis.x != 0.f ||
                               m_initialRotationAxis.y != 0.f ||
                               m_initialRotationAxis.z != 0.f)){
        graphics->rotate(glm::radians(m_initialAngle), m_initialRotationAxis);

    }
//    graphics->scale(transformComponent->getSize());
    graphics->scale(m_drawScale);
    graphics->setMaterial(m_material);
    glm::mat4x4 currentMatrix;
    for(int i=0; i<m_transforms.size(); i++){
        currentMatrix = aiMatToGlm(m_transforms[i]);
        graphics->setBones(i, currentMatrix);
    }
    graphics->drawShape(m_mesh->getShape());
}

glm::mat4 AnimationComponent::aiMatToGlm(aiMatrix4x4 mat){
    glm::mat4x4 newMat;
    newMat[0][0] = (GLfloat) mat.a1;
    newMat[1][0] = (GLfloat) mat.a2;
    newMat[2][0] = (GLfloat) mat.a3;
    newMat[3][0] = (GLfloat) mat.a4;

    newMat[0][1] = (GLfloat) mat.b1;
    newMat[1][1] = (GLfloat) mat.b2;
    newMat[2][1] = (GLfloat) mat.b3;
    newMat[3][1] = (GLfloat) mat.b4;

    newMat[0][2] = (GLfloat) mat.c1;
    newMat[1][2] = (GLfloat) mat.c2;
    newMat[2][2] = (GLfloat) mat.c3;
    newMat[3][2] = (GLfloat) mat.c4;

    newMat[0][3] = (GLfloat) mat.d1;
    newMat[1][3] = (GLfloat) mat.d2;
    newMat[2][3] = (GLfloat) mat.d3;
    newMat[3][3] = (GLfloat) mat.d4;

    return newMat;
}

void AnimationComponent::changeAnimation(int i){
    //std::cout << "load animation" << std::endl;
    m_mesh->loadAnimationMap(i, m_count);
}

void AnimationComponent::add(std::string name, float speed, float duration, float offset, float repeat){
    m_mesh->addAnimation(name, speed, duration, offset, repeat);
}

void AnimationComponent::update(int index, float speed, int repeat){
    m_mesh->updateAnimation(index, speed, repeat);
}

void AnimationComponent::changeCurrentAnimation(std::string name){
    m_mesh->setCurrentAnimation(name, m_count);
}

void AnimationComponent::setDrawScale(float scale){
    m_drawScale = glm::vec3(scale);
}

void AnimationComponent::setDrawScale(glm::vec3 scale){
    m_drawScale = scale;
}
glm::vec3 AnimationComponent::getDrawScale(){
    return m_drawScale;

}

float AnimationComponent::getAttackFrameSpeed(float attackSpeed, float numberOfFrames){
    float fps = 60.f;
    return attackSpeed * fps /numberOfFrames;
}
