#include "continuouscollisionsystem.h"

#include "engine/components/continuouscollisioncomponent.h"
#include "final/mapgeneration/chunkloadingsystem.h"
#include "engine/basics/gameobject.h"
#include "engine/components/trianglemeshcomponent.h"
#include "engine/collisionutils/ellipsoidtrianglecollision.h"
#include "engine/collisionutils/collisionshape.h"
#include "engine/components/physicscomponent.h"
#include "engine/components/transformcomponent.h"
#include "engine/components/collisioncomponent.h"
#include "engine/components/collisionresponsecomponent.h"
#include "engine/collisionutils/ellipsoid.h"

ContinuousCollisionSystem::ContinuousCollisionSystem(std::shared_ptr<ChunkLoadingSystem> chunkLoadingSystem) :
    TickSystem(TypeID::value<ContinuousCollisionComponent>()),
    m_chunkLoadingSystem(chunkLoadingSystem)
{

}

ContinuousCollisionSystem::~ContinuousCollisionSystem()
{

}

void ContinuousCollisionSystem::tick(float seconds)
{
    for(std::shared_ptr<Component> component : this->getComponents()){
        std::shared_ptr<ContinuousCollisionComponent> continuousComponent
                = std::dynamic_pointer_cast<ContinuousCollisionComponent>(component);
        if(continuousComponent){
            std::shared_ptr<TransformComponent> transform = component->getGameObject()->getComponent<TransformComponent>();
            std::shared_ptr<PhysicsComponent> physics = component->getGameObject()->getComponent<PhysicsComponent>();
            // update continuous collision triangles
            std::shared_ptr<EllipsoidTriangleCollision> ellipsoidTriangleCollision = continuousComponent->getEllipsoidTriangleCollision();
            QList<std::shared_ptr<Triangle>> collisionTriangles = getRelevantCollisionTriangles(continuousComponent, transform);
            ellipsoidTriangleCollision->updateTriangles(collisionTriangles);
            // trigger continuous collision response with movement vector
            std::shared_ptr<CollisionResponseComponent> collisionResponse = component->getGameObject()->getComponent<CollisionResponseComponent>();
            glm::vec3 movement = physics->getVelocity() * seconds;
            glm::vec3 adjustment = collisionResponse->collideContinuous(movement);
//            std::cout << "adjustment: " << adjustment << std::endl;
        }
        else{
            std::cout << "bad component in ContinuousCollisionSystem " << std::endl;
        }
    }
}

QList<std::shared_ptr<Triangle> > ContinuousCollisionSystem::getRelevantCollisionTriangles(std::shared_ptr<ContinuousCollisionComponent> continousComponent,
                                                                                           std::shared_ptr<TransformComponent> transformComponent){
    glm::vec3 radius = continousComponent->getEllipsoidTriangleCollision()->ellipsoid->radius;
    QSet<glm::ivec2> chunksToAdd;
    glm::vec3 center = transformComponent->getPosition();

    QList<glm::vec3> cornerOffsets = {glm::vec3(-1, 0, -1), glm::vec3(1, 0, -1), glm::vec3(-1, 0, 1), glm::vec3(1, 0, 1) };
    for(glm::vec3 cornerOffset : cornerOffsets){
        glm::vec3 corner = center + (radius * cornerOffset);
        glm::ivec2 chunkCoordinate = m_chunkLoadingSystem->getCell(corner);
        chunksToAdd.insert(chunkCoordinate);
    }
    //std::cout << "number chunks to add: " << chunksToAdd.size() << std::endl;

    QList<std::shared_ptr<Triangle>> collisionTriangles;
    QHash<glm::ivec2, std::shared_ptr<GameObject> > terrainObjects = m_chunkLoadingSystem->getTerrainObjects();

    for(glm::ivec2 chunkCoordinate : chunksToAdd){
        if(terrainObjects.contains(chunkCoordinate)){
            std::shared_ptr<GameObject> chunkObject = terrainObjects.value(chunkCoordinate);
            std::shared_ptr<TriangleMeshComponent> chunkTriangles = chunkObject->getComponent<TriangleMeshComponent>();
            QList<std::shared_ptr<Triangle>> triangles = chunkTriangles->getCollisionTriangles();
            for (std::shared_ptr<Triangle> &triangle : triangles) {
                collisionTriangles.append(triangle);
            }
        }
    }
    return collisionTriangles;
}

