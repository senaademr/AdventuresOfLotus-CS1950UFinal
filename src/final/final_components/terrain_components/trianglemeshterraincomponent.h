#ifndef TRIANGLEMESHTERRAINCOMPONENT_H
#define TRIANGLEMESHTERRAINCOMPONENT_H

//contains the nav polygons for a single chunk

#include "engine/components/component.h"
#include "engine/map/direction.h"
#include <QList>

class NavigationPolygon;

class TriangleMeshTerrainComponent : public Component
{
public:
    TriangleMeshTerrainComponent(QList<std::shared_ptr<NavigationPolygon>> navPolygons, glm::vec3 topLeft, int dimension);
    static void connect(std::shared_ptr<NavigationPolygon> triangle1, std::shared_ptr<NavigationPolygon> triangle2);
    static void disconnect(std::shared_ptr<NavigationPolygon> triangle1, std::shared_ptr<NavigationPolygon> triangle2);

    QList<std::shared_ptr<NavigationPolygon>> getNavPolygons();
    bool containsPoint(glm::vec3 point);

    void setNeighbor(std::shared_ptr<TriangleMeshTerrainComponent> neighbor, Direction dir);
    void removeNeighbor(std::shared_ptr<TriangleMeshTerrainComponent> neighbor, Direction dir);

private:
    //pair functions
    QList<std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > >
        getPairsLeft(std::shared_ptr<TriangleMeshTerrainComponent> neighbor);
    QList<std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > >
        getPairsRight(std::shared_ptr<TriangleMeshTerrainComponent> neighbor);
    QList<std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > >
        getPairsUp(std::shared_ptr<TriangleMeshTerrainComponent> neighbor);
    QList<std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > >
        getPairsDown(std::shared_ptr<TriangleMeshTerrainComponent> neighbor);

    void connectPairs(QList<std::pair<std::shared_ptr<NavigationPolygon>,
                                                    std::shared_ptr<NavigationPolygon> > > pairs);

    void disconnectPairs(QList<std::pair<std::shared_ptr<NavigationPolygon>,
                                                       std::shared_ptr<NavigationPolygon> > > pairs);
    void connectTriangleSquare(int row, int col);
    std::shared_ptr<NavigationPolygon> getTriangle(int row, int col, bool isBottomLeft);
    void connectTriangles();

private:
    QList<std::shared_ptr<NavigationPolygon>> m_navTriangles;
    glm::vec3 m_topLeft;
    int m_dimension;
};

#endif // TRIANGLEMESHTERRAINCOMPONENT_H
