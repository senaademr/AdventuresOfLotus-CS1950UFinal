#ifndef NAVIGATIONEDGE_H
#define NAVIGATIONEDGE_H

#include "edge.h"
#include <QList>

class NavigationPolygon;

class NavigationEdge : public Edge<NavigationPolygon>
{
public:
    NavigationEdge(std::shared_ptr<NavigationPolygon> vertexFrom, std::shared_ptr<NavigationPolygon> vertexTo, QList<glm::vec3> sharedVertices);

    std::shared_ptr<NavigationPolygon> getVertexFrom() override;
    std::shared_ptr<NavigationPolygon> getVertexTo() override;
    float getWeight() override;

    glm::vec3 getSharedVerticesMidpoint();

private:
    std::shared_ptr<NavigationPolygon> m_vertexFrom;
    std::shared_ptr<NavigationPolygon> m_vertexTo;
    QList<glm::vec3> m_sharedVertices;
    float m_weight;


};

#endif // NAVIGATIONEDGE_H
