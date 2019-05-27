#ifndef NAVIGATIONTRIANGLE_H
#define NAVIGATIONTRIANGLE_H

#include "navigationpolygon.h"
#include "engine/util/CommonIncludes.h"
#include <QList>

class NavigationTriangle : public NavigationPolygon
{
public:
    NavigationTriangle(const glm::vec3 &triangleVertex1, const glm::vec3 &triangleVertex2,const glm::vec3 &triangleVertex3);
    NavigationTriangle(QList<glm::vec3> &triangleVertices);


    // NavigationPolygon interface
public:
    bool pointInPolygon(const glm::vec3 &point) override;
    glm::vec3 getCenter() override;
    bool isAccessable() override;
    QList<glm::vec3> getVertices() override;

private:
    bool sameSide(const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &a, const glm::vec3 &b);

private:
    QList<glm::vec3> m_triangleVertices;
    std::unique_ptr<glm::vec3> m_center;
    bool m_isAccessable;
};

#endif // NAVIGATIONTRIANGLE_H
