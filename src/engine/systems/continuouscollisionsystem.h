#ifndef CONTINUOUSCOLLISIONSYSTEM_H
#define CONTINUOUSCOLLISIONSYSTEM_H
#include "engine/systems/ticksystem.h"

class ChunkLoadingSystem;
class Triangle;
class ContinuousCollisionComponent;
class TransformComponent;

class ContinuousCollisionSystem : public TickSystem
{
public:
    ContinuousCollisionSystem(std::shared_ptr<ChunkLoadingSystem> chunkLoadingSystem);
    ~ContinuousCollisionSystem() override;
    void tick(float seconds) override;

    void resolveMovement(std::shared_ptr<GameObject> gameObject, glm::vec3 mtv);
    void resolveMovement(std::shared_ptr<ContinuousCollisionComponent> continuousComponent, glm::vec3 startPos, glm::vec3 endPos);
private:

    QList<std::shared_ptr<Triangle> > getRelevantCollisionTriangles(std::shared_ptr<ContinuousCollisionComponent> continousComponent,
                                                                    std::shared_ptr<TransformComponent> transformComponent);
private:
    std::shared_ptr<ChunkLoadingSystem> m_chunkLoadingSystem;
};

#endif // CONTINUOUSCOLLISIONSYSTEM_H
