#include "navigationmesh.h"

#include "navigationpolygon.h"
#include "navigationedge.h"
#include "final/final_components/terrain_components/trianglemeshterraincomponent.h"

#include "navigationtriangle.h"
#include "astar.h"
#include "graphpath.h"
#include "engine/util/util.h"

NavigationMesh::NavigationMesh()
{
}


QList<glm::vec3> NavigationMesh::navigate(const glm::vec3 &start, const glm::vec3 &end){
    std::shared_ptr<NavigationPolygon> startPolygon = findPolygonWithPoint(start);
    std::shared_ptr<NavigationPolygon> endPolygon = findPolygonWithPoint(end);
    if(startPolygon == nullptr || endPolygon == nullptr){
//        std::cout << "cannot find path between: " << start  << " and: " << end;
//        if(startPolygon == nullptr){
//            std::cout << "  start is not on the map";
//        }
//        if(endPolygon == nullptr){
//            std::cout << "  end is not on the map";
//        }
//        std::cout <<". returning empty list" << std::endl;
        return QList<glm::vec3>();
    }
    if(startPolygon == endPolygon){
        //std::cout << "start and end are both in the same polygon" << std::endl;
        QList<glm::vec3> result;
        result.append(start);
        result.append(end);
        return result;
    }
    //std::cout << "points are in different polygons" << std::endl;

    auto heuristic = [endPolygon](std::shared_ptr<NavigationPolygon> polygon) {
        return glm::distance2(polygon->getCenter(), endPolygon->getCenter());
    };

    auto path = AStar::findPath<NavigationPolygon, NavigationEdge>(startPolygon, endPolygon, heuristic);
//    std::cout << "path length: " << path->getTotalLength() << std::endl;
    return constructPath(path, start, end);
}

QList<glm::vec3> NavigationMesh::constructPath(std::shared_ptr<GraphPath<NavigationPolygon, NavigationEdge> > path,
                                               const glm::vec3 &start, const glm::vec3 &end){
    QList<glm::vec3> constructedPath;
    if(path->getNumEdges() == 0){
        return constructedPath;
    }
    constructedPath.append(start);
    for(int i = 0; i < path->getNumEdges(); i ++){
        std::shared_ptr<NavigationEdge> edge = path->getEdge(i);
        constructedPath.append(edge->getSharedVerticesMidpoint());
    }
    constructedPath.append(end);
    return constructedPath;
}
void NavigationMesh::addChunk(std::shared_ptr<TriangleMeshTerrainComponent> triangleMeshChunk){
    m_navigationChunks.append(triangleMeshChunk);
}

void NavigationMesh::removeChunk(std::shared_ptr<TriangleMeshTerrainComponent> triangleMeshChunk){
    m_navigationChunks.removeOne(triangleMeshChunk);

}

std::shared_ptr<NavigationPolygon> NavigationMesh::findPolygonWithPoint(glm::vec3 vertex){
    QList<std::shared_ptr<NavigationPolygon>> navPolygons;
    for(std::shared_ptr<TriangleMeshTerrainComponent> chunk : m_navigationChunks){
        if(chunk->containsPoint(vertex)){
            for(std::shared_ptr<NavigationPolygon> navPolygon : chunk->getNavPolygons()){
                if(navPolygon->pointInPolygon(vertex)){
                    navPolygons.append(navPolygon);
                }
            }
        }
    }

    if(navPolygons.size() == 0){
        return nullptr;

    }
//    std::cout << "num polygons that have point: " << navPolygons.size() << std::endl;
    return navPolygons.at(0);
}

//void NavigationMesh::addTriangle(const glm::vec3 &vertex1, const glm::vec3 &vertex2, const glm::vec3 &vertex3){
//    QList<glm::vec3> triangleVertices;
//    triangleVertices.append(vertex1);
//    triangleVertices.append(vertex2);
//    triangleVertices.append(vertex3);
//    addTriangle(triangleVertices);
//}

//void NavigationMesh::addTriangle(QList<glm::vec3> &triangleVertices){
//    //std::cout << "adding triangle" << std::endl;

//    std::shared_ptr<NavigationTriangle> triangle = std::make_shared<NavigationTriangle>(triangleVertices);
//    addPolygon(triangle);

//}

//void NavigationMesh::addPolygon(std::shared_ptr<NavigationPolygon> navPolygon){
//    m_navigationPolygons.append(navPolygon);
//}

//void NavigationMesh::removePolygon(std::shared_ptr<NavigationPolygon> navPolygon){
//    m_navigationPolygons.removeOne(navPolygon);
//}

bool NavigationMesh::verticesNearlyEqual(const glm::vec3 &vertex1, const glm::vec3 &vertex2, float epsilon){
    return glm::distance2(vertex1, vertex2) < epsilon*epsilon;
}

QList<glm::vec3> NavigationMesh::findSharedVertices(QList<glm::vec3> &vertices1, QList<glm::vec3> &vertices2){
    QList<glm::vec3> sharedVertices;
    for(int index1 = 0; index1 < vertices1.size(); index1 ++){
        glm::vec3 vertex1 = vertices1.at(index1);
        for(int index2 = 0; index2 < vertices2.size(); index2 ++){
            glm::vec3 vertex2 = vertices2.at(index2);
            if(verticesNearlyEqual(vertex1, vertex2)){
                sharedVertices.append(vertex1); //should I average them?
            }
        }
    }
    return sharedVertices;
}

