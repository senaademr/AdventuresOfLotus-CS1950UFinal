#include "trianglemeshterraincomponent.h"

#include "engine/navigation/navigationmesh.h"
#include "engine/navigation/navigationpolygon.h"
#include "engine/navigation/navigationedge.h"
#include "engine/util/util.h"

TriangleMeshTerrainComponent::TriangleMeshTerrainComponent(QList<std::shared_ptr<NavigationPolygon>> navPolygons, glm::vec3 topLeft, int dimension):
    m_navTriangles(navPolygons),
    m_topLeft(topLeft),
    m_dimension(dimension)
{
    connectTriangles();
}


QList<std::shared_ptr<NavigationPolygon> > TriangleMeshTerrainComponent::getNavPolygons(){
    return m_navTriangles;
}

bool TriangleMeshTerrainComponent::containsPoint(glm::vec3 point){
    return (point.x >= m_topLeft.x) && (point.x <= m_topLeft.x + m_dimension)
            && (point.z >= m_topLeft.z) && (point.z <= m_topLeft.z + m_dimension);

}

std::shared_ptr<NavigationPolygon> TriangleMeshTerrainComponent::getTriangle(int row, int col, bool isBottomLeft){
    assert(row >= 0 && col >= 0);
    assert(row < m_dimension && col < m_dimension);
    int index = (row*m_dimension + col)* 2;
    assert(index+1 < m_navTriangles.size());
    if(isBottomLeft){
        return m_navTriangles.at(index);
    }
    else{
        return m_navTriangles.at(index+1);
    }

}

void TriangleMeshTerrainComponent::connect(std::shared_ptr<NavigationPolygon> triangle1, std::shared_ptr<NavigationPolygon> triangle2){
    QList<glm::vec3> triangle1Vertices = triangle1->getVertices();
    QList<glm::vec3> triangle2Vertices = triangle2->getVertices();
    QList<glm::vec3> shared = NavigationMesh::findSharedVertices(triangle1Vertices, triangle2Vertices);

    if(shared.size() != 2){
        std::cout << "Warning: wrong number of shared vertices. Number: " << shared.size() << std::endl;
        std::cout << "Triangle1 : ";
        for(glm::vec3 vertex : triangle1Vertices){
            std::cout << vertex << ", ";
        }
        std::cout << std::endl;
        std::cout << "Triangle2 : ";
        for(glm::vec3 vertex : triangle2Vertices){
            std::cout << vertex << ", ";
        }
        std::cout << std::endl;
        throw -1;
    }

    //TODO: calculate shared differently?
    std::shared_ptr<NavigationEdge> edge1 = std::make_shared<NavigationEdge>(triangle1, triangle2, shared);
    std::shared_ptr<NavigationEdge> edge2 = std::make_shared<NavigationEdge>(triangle2, triangle1, shared);
    triangle1->addEdge(edge1);
    triangle2->addEdge(edge2);

}

void TriangleMeshTerrainComponent::disconnect(std::shared_ptr<NavigationPolygon> triangle1, std::shared_ptr<NavigationPolygon> triangle2){
    triangle1->removeNeighbor(triangle2);
    triangle2->removeNeighbor(triangle1);
}


void TriangleMeshTerrainComponent::connectTriangleSquare(int row, int col){

    std::shared_ptr<NavigationPolygon> curBottomLeft = getTriangle(row, col, true);
    std::shared_ptr<NavigationPolygon> curTopRight = getTriangle(row, col, false);
    connect(curBottomLeft, curTopRight);

    if(col < m_dimension-1){
        std::shared_ptr<NavigationPolygon> rightBottomLeft = getTriangle(row, col+1, true);
        connect(curTopRight, rightBottomLeft);
    }
    if(row < m_dimension-1){
        std::shared_ptr<NavigationPolygon> bottomTopRight = getTriangle(row+1, col, false);
        connect(curBottomLeft, bottomTopRight);
    }

    //connect bottomLeft topRight

}

void TriangleMeshTerrainComponent::connectTriangles(){
    assert(m_navTriangles.size() == m_dimension*m_dimension*2);
    for(int row = 0; row < m_dimension; row ++){
        for(int col = 0; col < m_dimension; col ++){
            connectTriangleSquare(row, col);
        }
    }
}

//void TriangleMeshTerrainComponent::connectNeighborLeft(std::shared_ptr<TriangleMeshTerrainComponent> neighbor){
//
//    for(int row = 0; row < m_dimension; row ++){
//        std::shared_ptr<NavigationPolygon> leftTriangle = getTriangle(row, 0, true);
//        std::shared_ptr<NavigationPolygon> rightTriangle = neighbor->getTriangle(row, m_dimension-1, false);
//        connect(leftTriangle, rightTriangle);
//    }
//}

QList<std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > >
    TriangleMeshTerrainComponent::getPairsLeft(std::shared_ptr<TriangleMeshTerrainComponent> neighbor){
    //connect left side of this with right side of neighbor
    QList<std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > > pairs;
    for(int row = 0; row < m_dimension; row ++){
        std::shared_ptr<NavigationPolygon> leftTriangle = getTriangle(row, 0, true);
        std::shared_ptr<NavigationPolygon> rightTriangle = neighbor->getTriangle(row, m_dimension-1, false);
        auto pair = std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> >(leftTriangle, rightTriangle);
        pairs.append(pair);
    }
    return pairs;
}

QList<std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > >
    TriangleMeshTerrainComponent::getPairsRight(std::shared_ptr<TriangleMeshTerrainComponent> neighbor){
    //connect right side of this with left side of neighbor
    QList<std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > > pairs;
    for(int row = 0; row < m_dimension; row ++){
        std::shared_ptr<NavigationPolygon> rightTriangle = getTriangle(row, m_dimension-1, false);
        std::shared_ptr<NavigationPolygon> leftTriangle = neighbor->getTriangle(row, 0, true);
        auto pair = std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> >(leftTriangle, rightTriangle);
        pairs.append(pair);
    }
    return pairs;
}

QList<std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > >
    TriangleMeshTerrainComponent::getPairsUp(std::shared_ptr<TriangleMeshTerrainComponent> neighbor){
    //connect top side of this with bottom side of neighbor
    QList<std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > > pairs;
    for(int col = 0; col< m_dimension; col++){
        std::shared_ptr<NavigationPolygon> topTriangle = getTriangle(0, col, false);
        std::shared_ptr<NavigationPolygon> bottomTriangle = neighbor->getTriangle(m_dimension-1, col, true);
        auto pair = std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> >(topTriangle, bottomTriangle);
        pairs.append(pair);
    }
    return pairs;
}

QList<std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > >
    TriangleMeshTerrainComponent::getPairsDown(std::shared_ptr<TriangleMeshTerrainComponent> neighbor){
    //connect bottom side of this with top side of neighbor
    QList<std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > > pairs;
    for(int col = 0; col< m_dimension; col++){
        std::shared_ptr<NavigationPolygon> bottomTriangle = getTriangle(m_dimension-1, col, true);
        std::shared_ptr<NavigationPolygon> topTriangle = neighbor->getTriangle(0, col, false);
        auto pair = std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> >(bottomTriangle, topTriangle);
        pairs.append(pair);
    }
    return pairs;
}

void TriangleMeshTerrainComponent::connectPairs(QList<std::pair<std::shared_ptr<NavigationPolygon>,
                                                std::shared_ptr<NavigationPolygon> > > pairs){
    for(std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > pair : pairs){
        connect(pair.first, pair.second);
    }
}

void TriangleMeshTerrainComponent::disconnectPairs(QList<std::pair<std::shared_ptr<NavigationPolygon>,
                                                   std::shared_ptr<NavigationPolygon> > > pairs){
    for(std::pair<std::shared_ptr<NavigationPolygon>, std::shared_ptr<NavigationPolygon> > pair : pairs){
        disconnect(pair.first, pair.second);
    }
}

void TriangleMeshTerrainComponent::setNeighbor(std::shared_ptr<TriangleMeshTerrainComponent> neighbor, Direction dir){
    switch(dir){
    case Direction::UP:
        connectPairs(getPairsUp(neighbor));
        break;
    case Direction::DOWN:
        connectPairs(getPairsDown(neighbor));
        break;
    case Direction::LEFT:
        connectPairs(getPairsLeft(neighbor));
        break;
    case Direction::RIGHT:
        connectPairs(getPairsRight(neighbor));
        break;
    }

}

void TriangleMeshTerrainComponent::removeNeighbor(std::shared_ptr<TriangleMeshTerrainComponent> neighbor, Direction dir){
    switch(dir){
    case Direction::UP:
        disconnectPairs(getPairsUp(neighbor));
        break;
    case Direction::DOWN:
        disconnectPairs(getPairsDown(neighbor));
        break;
    case Direction::LEFT:
        disconnectPairs(getPairsLeft(neighbor));
        break;
    case Direction::RIGHT:
        disconnectPairs(getPairsRight(neighbor));
        break;
    }

}
