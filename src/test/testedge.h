#ifndef TESTEDGE_H
#define TESTEDGE_H

#include "engine/util/CommonIncludes.h"
#include "engine/navigation/edge.h"

class TestVertex;

class TestEdge : public Edge<TestVertex>
{
public:
    TestEdge(std::shared_ptr<TestVertex> vertexFrom, std::shared_ptr<TestVertex> vertexTo, float weight);

    // Edge interface
public:
    std::shared_ptr<TestVertex> getVertexFrom();
    std::shared_ptr<TestVertex> getVertexTo();

    float getWeight();

private:
    std::shared_ptr<TestVertex> m_vertexFrom;
    std::shared_ptr<TestVertex> m_vertexTo;
    float m_weight;
};

#endif // TESTEDGE_H
