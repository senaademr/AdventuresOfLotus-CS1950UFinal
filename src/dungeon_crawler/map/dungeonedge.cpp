#include "dungeonedge.h"

#include "dungeonvertex.h"

DungeonEdge::DungeonEdge(std::shared_ptr<DungeonVertex> vertexFrom, std::shared_ptr<DungeonVertex> vertexTo) :
    m_vertexFrom(vertexFrom),
    m_vertexTo(vertexTo),
    m_direction(calculateDirection(m_vertexFrom, m_vertexTo)),
    m_weight(calculateWeight(m_vertexFrom, m_vertexTo))
{
}

std::shared_ptr<DungeonVertex> DungeonEdge::getVertexFrom(){
    return m_vertexFrom;
}

std::shared_ptr<DungeonVertex> DungeonEdge::getVertexTo(){
    return m_vertexTo;
}

float DungeonEdge::calculateWeight(std::shared_ptr<DungeonVertex> vertexFrom, std::shared_ptr<DungeonVertex> vertexTo){
    return glm::distance(vertexFrom->getPosition(), vertexTo->getPosition());
}
glm::vec3 DungeonEdge::calculateDirection(std::shared_ptr<DungeonVertex> vertexFrom, std::shared_ptr<DungeonVertex> vertexTo){
    return glm::normalize(vertexTo->getPosition()- vertexFrom->getPosition());
}

glm::vec3 DungeonEdge::getDirection(){
    return m_direction;
}

float DungeonEdge::getWeight(){
    return m_weight;
}
