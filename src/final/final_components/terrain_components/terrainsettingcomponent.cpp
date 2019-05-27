#include "terrainsettingcomponent.h"

#include "engine/map_generation/noisefunction.h"
#include "engine/basics/gameobject.h"
#include "engine/components/transformcomponent.h"
#include "engine/components/physicscomponent.h"

TerrainSettingComponent::TerrainSettingComponent()
    : m_noise(nullptr)
{
}


void TerrainSettingComponent::setNoise(std::shared_ptr<NoiseFunction> noise){
    m_noise = noise;
}

void TerrainSettingComponent::tick(float seconds){
    if(m_noise){
        std::shared_ptr<GameObject> gameObject = this->getGameObject();
        std::shared_ptr<TransformComponent> transformComponent =
                gameObject->getComponent<TransformComponent>();
        std::shared_ptr<PhysicsComponent> physics =
                gameObject->getComponent<PhysicsComponent>();
        float y = m_noise->interpolatedNoise(glm::vec2(transformComponent->getPosition().x,transformComponent->getPosition().z));
        if (y > transformComponent->getPosition().y) {
            transformComponent->setY(y);
            physics->setYVelocity(0);
        }
        //std::cout << "player position: " << transformComponent->getPosition() << std::endl;
    }
}
