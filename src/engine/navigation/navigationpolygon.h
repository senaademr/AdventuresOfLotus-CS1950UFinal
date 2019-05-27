#ifndef NAVIGATIONPOLYGON_H
#define NAVIGATIONPOLYGON_H

#include "glm/glm.hpp"

#include "engine/navigation/vertex.h"
#include <QSet>

class NavigationEdge;

class NavigationPolygon : public Vertex<NavigationEdge>
{
public:
    //returns true if point is within polygon, false otherwise
    NavigationPolygon();

    virtual bool pointInPolygon(const glm::vec3 &point) = 0;
    virtual glm::vec3 getCenter() = 0;
    virtual bool isAccessable() = 0;
    virtual QList<glm::vec3> getVertices() = 0;

    void removeEdge(std::shared_ptr<NavigationEdge> edge);
    void removeNeighbor(std::shared_ptr<NavigationPolygon> neighbor);

    void addEdge(std::shared_ptr<NavigationEdge> edge);
    QList<std::shared_ptr<NavigationEdge>> getEdges();

private:

    QList<std::shared_ptr<NavigationEdge> > m_edges;

};

inline uint qHash(const std::shared_ptr<NavigationPolygon> &v){
    return qHash((v.get()));
}

inline bool operator==(const std::shared_ptr<NavigationPolygon> &v1, const std::shared_ptr<NavigationPolygon> &v2)
{
    return (v1.get()) == (v2.get());
}
inline bool operator!=(const std::shared_ptr<NavigationPolygon> &v1, const std::shared_ptr<NavigationPolygon> &v2)
{
    return !(v1 == v2);
}

#endif // NAVIGATIONPOLYGON_H
