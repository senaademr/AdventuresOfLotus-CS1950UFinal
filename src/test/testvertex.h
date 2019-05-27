#ifndef TESTVERTEX_H
#define TESTVERTEX_H

#include <QSet>
#include "engine/util/CommonIncludes.h"
#include "engine/navigation/vertex.h"

class TestEdge;

class TestVertex : public Vertex<TestEdge>
{
public:
    TestVertex(std::string name);

public:
    QList<std::shared_ptr<TestEdge> > getEdges();

    void addEdge(std::shared_ptr<TestEdge>  edge);
    std::string getName();

private:
    QList<std::shared_ptr<TestEdge> > m_edges;
    std::string m_name;

};

inline uint qHash(const std::shared_ptr<TestVertex> &v){
    return qHash((v.get()));
}

inline bool operator==(const std::shared_ptr<TestVertex> &v1, const std::shared_ptr<TestVertex> &v2)
{
    return (v1.get()) == (v2.get());
}

#endif // TESTVERTEX_H
