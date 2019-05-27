#include "dungeonvertex.h"

#include "dungeonedge.h"

DungeonVertex::DungeonVertex(glm::vec3 position) : Vertex(),
    m_position(position){

}


void DungeonVertex::connectDungeonVertices(std::shared_ptr<DungeonVertex> v1, std::shared_ptr<DungeonVertex> v2){
    std::shared_ptr<DungeonEdge> edge1 = std::make_shared<DungeonEdge>(v1, v2);
    v1->addEdge(edge1);

    std::shared_ptr<DungeonEdge> edge2 = std::make_shared<DungeonEdge>(v2, v1);
    v2->addEdge(edge2);
}


void DungeonVertex::removeFromGraph(){
    for(std::shared_ptr<DungeonEdge> edge : m_edges){
        std::shared_ptr<DungeonVertex> other = edge->getVertexTo();
        other->removeEdgeConnectingTo(shared_from_this());
    }

}

void DungeonVertex::removeEdgeConnectingTo(std::shared_ptr<DungeonVertex> other){
    std::shared_ptr<DungeonEdge> edgeToRemove = nullptr;
    for(std::shared_ptr<DungeonEdge> edge : m_edges){
        if(edge->getVertexTo() == other){
            edgeToRemove = edge;
            break;
        }
    }
    //assert(edgeToRemove);
    if(edgeToRemove){
        m_edges.removeOne(edgeToRemove);

    }

}

QList<std::shared_ptr<DungeonEdge> > DungeonVertex::getEdges(){
    return m_edges;

}

void DungeonVertex::addEdge(std::shared_ptr<DungeonEdge>  edge){
    m_edges.append(edge);
}


glm::vec3 DungeonVertex::getPosition(){
    return m_position;
}

std::string DungeonVertex::toString(){
    return "DungeonVertex: " + glm::to_string(m_position);
}
