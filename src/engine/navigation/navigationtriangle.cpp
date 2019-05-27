#include "navigationtriangle.h"

#include "navigationedge.h"

NavigationTriangle::NavigationTriangle(const glm::vec3 &triangleVertex1, const glm::vec3 &triangleVertex2,const glm::vec3 &triangleVertex3)
    : m_center(nullptr),
      m_isAccessable(true)
{
    m_triangleVertices.append(triangleVertex1);
    m_triangleVertices.append(triangleVertex2);
    m_triangleVertices.append(triangleVertex3);

}

NavigationTriangle::NavigationTriangle(QList<glm::vec3> &triangleVertices)
    : m_triangleVertices(triangleVertices),
      m_center(nullptr),
      m_isAccessable(true)
{
    assert(m_triangleVertices.size() == 3);
}

bool NavigationTriangle::pointInPolygon(const glm::vec3 &point){
    glm::vec3 removeY = glm::vec3(1, 0, 1);
    glm::vec3 a = m_triangleVertices.at(0)* removeY;
    glm::vec3 b = m_triangleVertices.at(1)* removeY;
    glm::vec3 c = m_triangleVertices.at(2)* removeY;

    glm::vec3 p = point * removeY;

    return sameSide(p, a, b, c) && sameSide(p, b, a, c) && sameSide(p, c, a, b);
}

glm::vec3 NavigationTriangle::getCenter(){
    if(!m_center){
        glm::vec3 a = m_triangleVertices.at(0);
        glm::vec3 b = m_triangleVertices.at(1);
        glm::vec3 c = m_triangleVertices.at(2);

        float x = (a.x + b.x + c.x) /3.f;
        float y = (a.y + b.y + c.y) /3.f;
        float z = (a.z + b.z + c.z) /3.f;
        m_center = std::make_unique<glm::vec3>(x, y, z);
    }
    assert(m_center);
    return *(m_center.get());
}

bool NavigationTriangle::isAccessable(){
    return m_isAccessable;
}

QList<glm::vec3> NavigationTriangle::getVertices(){
    return m_triangleVertices;
}


bool NavigationTriangle::sameSide(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &a, const glm::vec3 &b){
    glm::vec3 crossProduct1 = glm::cross(b-a, p1-a);
    glm::vec3 crossProduct2 = glm::cross(b-a, p2-a);
    return glm::dot(crossProduct1, crossProduct2) >= 0;
}
