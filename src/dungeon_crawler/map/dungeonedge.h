#ifndef DUNGEONEDGE_H
#define DUNGEONEDGE_H

#include "engine/util/CommonIncludes.h"
#include "engine/navigation/edge.h"

class DungeonVertex;

class DungeonEdge : public Edge<DungeonVertex>
{
public:
    DungeonEdge(std::shared_ptr<DungeonVertex> vertexFrom, std::shared_ptr<DungeonVertex> vertexTo);

    static float calculateWeight(std::shared_ptr<DungeonVertex> vertexFrom, std::shared_ptr<DungeonVertex> vertexTo);
    static glm::vec3 calculateDirection(std::shared_ptr<DungeonVertex> vertexFrom, std::shared_ptr<DungeonVertex> vertexTo);
    // Edge interface
public:
    std::shared_ptr<DungeonVertex> getVertexFrom();
    std::shared_ptr<DungeonVertex> getVertexTo();

    float getWeight();
    glm::vec3 getDirection();

private:
    std::shared_ptr<DungeonVertex> m_vertexFrom;
    std::shared_ptr<DungeonVertex> m_vertexTo;
    glm::vec3 m_direction;
    float m_weight;

};

#endif // DUNGEONEDGE_H
