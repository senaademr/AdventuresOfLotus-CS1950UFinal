#include "testvertex.h"

TestVertex::TestVertex(std::string name):
    Vertex(),
     m_name(name)
{

}

QList<std::shared_ptr<TestEdge> > TestVertex::getEdges(){
    return m_edges;

}

void TestVertex::addEdge(std::shared_ptr<TestEdge>  edge){
    m_edges.append(edge);
}

std::string TestVertex::getName(){
    return m_name;
}
