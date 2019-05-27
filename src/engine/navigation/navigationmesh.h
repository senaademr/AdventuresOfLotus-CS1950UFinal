#ifndef NAVIGATIONMESH_H
#define NAVIGATIONMESH_H

#include "engine/util/CommonIncludes.h"
#include <QList>
#include "engine/navigation/graphpath.h"
//https://medium.com/@mscansian/a-with-navigation-meshes-246fd9e72424

class NavigationPolygon;
class NavigationEdge;
class TriangleMeshTerrainComponent;

class NavigationMesh
{
public:
    NavigationMesh();

    //takes in start position and end position. returns list of vertices that the input should go through to get there
    QList<glm::vec3> navigate(const glm::vec3 &start, const glm::vec3 &end);
    std::shared_ptr<NavigationPolygon> findPolygonWithPoint(glm::vec3 vertex);

    void addTriangle(QList<glm::vec3> &triangleVertices);
    void addTriangle(const glm::vec3 &vertex1, const glm::vec3 &vertex2, const glm::vec3 &vertex3);

//    void addPolygon(std::shared_ptr<NavigationPolygon> navPolygon);
//    void removePolygon(std::shared_ptr<NavigationPolygon> navPolygon);
    void addChunk(std::shared_ptr<TriangleMeshTerrainComponent> triangleMeshChunk);
    void removeChunk(std::shared_ptr<TriangleMeshTerrainComponent> triangleMeshChunk);

    static bool verticesNearlyEqual(const glm::vec3 &vertex1, const glm::vec3 &vertex2, float epsilon = .00001);
    static QList<glm::vec3> findSharedVertices(QList<glm::vec3> &vertices1, QList<glm::vec3> &vertices2);
private:
    QList<glm::vec3> constructPath(std::shared_ptr<GraphPath<NavigationPolygon, NavigationEdge> > path, const glm::vec3 &start, const glm::vec3 &end);

private:
    QList<std::shared_ptr<TriangleMeshTerrainComponent> > m_navigationChunks;
    //QList<std::shared_ptr<NavigationPolygon>> m_navigationPolygons;
//    QHash<glm::vec3, std::shared_ptr<QList<std::shared_ptr<NavigationPolygon>>>> m_verticesToPolygon;

};


#endif // NAVIGATIONMESH_H
