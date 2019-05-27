#ifndef DUNGEONVERTEX_H
#define DUNGEONVERTEX_H

#include "engine/navigation/vertex.h"
#include <QSet>


class DungeonEdge;

class DungeonVertex : public Vertex<DungeonEdge>, public std::enable_shared_from_this<DungeonVertex>
{
public:
    DungeonVertex(glm::vec3 position);

    static void connectDungeonVertices(std::shared_ptr<DungeonVertex> v1, std::shared_ptr<DungeonVertex> v2);

public:
    QList<std::shared_ptr<DungeonEdge> > getEdges();

    void addEdge(std::shared_ptr<DungeonEdge>  edge);
    glm::vec3 getPosition();

    std::string toString();
    void removeFromGraph();
private:

    void removeEdgeConnectingTo(std::shared_ptr<DungeonVertex> other);

private:

    QList<std::shared_ptr<DungeonEdge> > m_edges;
    const glm::vec3 m_position;
};

inline std::ostream& operator<< (std::ostream& stream,const std::shared_ptr<DungeonVertex>& vertex) {
    return stream << vertex->toString();
}

inline uint qHash(const std::shared_ptr<DungeonVertex> &v){
    return qHash((v.get()));
}

inline bool operator==(const std::shared_ptr<DungeonVertex> &v1, const std::shared_ptr<DungeonVertex> &v2)
{
    return (v1.get()) == (v2.get());
}
inline bool operator!=(const std::shared_ptr<DungeonVertex> &v1, const std::shared_ptr<DungeonVertex> &v2)
{
    return !(v1 == v2);
}
#endif // DUNGEONVERTEX_H
