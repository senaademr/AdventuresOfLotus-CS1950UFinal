#include "testedge.h"

TestEdge::TestEdge(std::shared_ptr<TestVertex> vertexFrom, std::shared_ptr<TestVertex> vertexTo, float weight) :
    m_vertexFrom(vertexFrom),
    m_vertexTo(vertexTo),
    m_weight(weight)
{
}

std::shared_ptr<TestVertex> TestEdge::getVertexFrom(){
    return m_vertexFrom;
}

std::shared_ptr<TestVertex> TestEdge::getVertexTo(){
    return m_vertexTo;
}

float TestEdge::getWeight(){
    return m_weight;
}
