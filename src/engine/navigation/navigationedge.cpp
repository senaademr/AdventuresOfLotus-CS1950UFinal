#include "navigationedge.h"

#include "navigationpolygon.h"
#include <math.h>

NavigationEdge::NavigationEdge(std::shared_ptr<NavigationPolygon> vertexFrom, std::shared_ptr<NavigationPolygon> vertexTo, QList<glm::vec3> sharedVertices)
    : m_vertexFrom(vertexFrom),
      m_vertexTo(vertexTo),
      m_sharedVertices(sharedVertices),
      m_weight(NAN)
{
    assert(m_sharedVertices.size() == 2);
}

std::shared_ptr<NavigationPolygon> NavigationEdge::getVertexFrom(){
    return m_vertexFrom;
}
std::shared_ptr<NavigationPolygon> NavigationEdge::getVertexTo(){
    return m_vertexTo;
}

float NavigationEdge::getWeight() {
    if(isnan(m_weight)){
        glm::vec3 vertex1 = m_vertexFrom->getCenter();
        glm::vec3 vertex2 = m_vertexTo->getCenter();

        m_weight = glm::distance(vertex1, vertex2);
    }
    assert(!isnan(m_weight));
    return m_weight;

}


glm::vec3 NavigationEdge::getSharedVerticesMidpoint(){
    return (m_sharedVertices.at(0) + m_sharedVertices.at(1)) /2.f;
}

