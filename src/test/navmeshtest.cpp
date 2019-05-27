#include "navmeshtest.h"

#include "engine/util/util.h"
#include "engine/navigation/navigationedge.h"
#include "engine/navigation/navigationtriangle.h"

#include "engine/util/CommonIncludes.h"

#include "engine/navigation/navigationmesh.h"
#include <assert.h>

NavmeshTest::NavmeshTest()
{
}

void NavmeshTest::runTests(){
    std::cout << "running navmesh tests" << std::endl;
    testPointInTriangle();
    test3DPointInTriangle();
    testInSameTriangle();
//    testInDifferentTriangle();
//    testTwoByTwo();
//    testPointInTriangleClose();
    std::cout << "passed all navmesh tests" << std::endl;
}

void NavmeshTest::testPointInTriangle(){
    QList<glm::vec3> vertices1 = {glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1)};
    std::shared_ptr<NavigationTriangle> navTriangle
            = std::make_shared<NavigationTriangle>(vertices1);
    assert(navTriangle->pointInPolygon(glm::vec3(.1, 0, -.1)));
    assert(navTriangle->pointInPolygon(glm::vec3(.1, 5, -.1)));
    assert(navTriangle->pointInPolygon(vertices1.at(0)));
    assert(navTriangle->pointInPolygon(vertices1.at(1)));
    assert(navTriangle->pointInPolygon(vertices1.at(2)));

    assert(!navTriangle->pointInPolygon(glm::vec3(-1, 0 ,0)));
    assert(!navTriangle->pointInPolygon(glm::vec3(0, 0 ,.2)));
}

void NavmeshTest::test3DPointInTriangle(){
    QList<glm::vec3> vertices1 = {glm::vec3(0, -.5, 0), glm::vec3(1, 5, 0), glm::vec3(0, 2, -1)};
    std::shared_ptr<NavigationTriangle> navTriangle
            = std::make_shared<NavigationTriangle>(vertices1);
    assert(navTriangle->pointInPolygon(glm::vec3(.1, 0, -.1)));
    assert(navTriangle->pointInPolygon(glm::vec3(.1, 5, -.1)));
    assert(navTriangle->pointInPolygon(vertices1.at(0)));
    assert(navTriangle->pointInPolygon(vertices1.at(1)));
    assert(navTriangle->pointInPolygon(vertices1.at(2)));

    assert(!navTriangle->pointInPolygon(glm::vec3(-1, 0 ,0)));
    assert(!navTriangle->pointInPolygon(glm::vec3(0, 0 ,.2)));
}

void NavmeshTest::testPointInTriangleClose(){
//    QList<glm::vec3> vertices1 = {glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1)};
//    QList<glm::vec3> vertices2 = {glm::vec3(1, 0, 0), glm::vec3(1, 0, -1), glm::vec3(0, 0, -1)};
//    std::shared_ptr<NavigationMesh> navMesh = std::make_shared<NavigationMesh>();
//    navMesh->addTriangle(vertices1);
//    navMesh->addTriangle(vertices2);
//    glm::vec3 start = glm::vec3(.49, 0, -.49);
//    glm::vec3 end = glm::vec3(.51, 0, -.51);
//    QList<glm::vec3> path = navMesh->navigate(start, end);


}

void NavmeshTest::testInSameTriangle(){
//    QList<glm::vec3> vertices1 = {glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1)};
//    QList<glm::vec3> vertices2 = {glm::vec3(1, 0, 0), glm::vec3(1, 0, -1), glm::vec3(0, 0, -1)};

//    std::shared_ptr<NavigationMesh> navMesh = std::make_shared<NavigationMesh>();
//    navMesh->addTriangle(vertices1);
//    navMesh->addTriangle(vertices2);
//    glm::vec3 start =glm::vec3(.1, 0, -.1);
//    glm::vec3 end = glm::vec3(.2, 0, -.2);
//    QList<glm::vec3> path = navMesh->navigate(start, end);
//    assert(path.size() == 2);
//    assert(NavigationMesh::verticesNearlyEqual(start, path.at(0)));
//    assert(NavigationMesh::verticesNearlyEqual(end, path.at(1)));

}


void NavmeshTest::addSquare(std::shared_ptr<NavigationMesh> navMesh, glm::vec3 bottomLeft){
//    glm::vec3 bottomRight = bottomLeft + glm::vec3(1, 0, 0);
//    glm::vec3 topLeft = bottomLeft + glm::vec3(0, 0, -1);
//    glm::vec3 topRight = bottomLeft + glm::vec3(1, 0, -1);
//    QList<glm::vec3> vertices1 = {bottomLeft, bottomRight, topLeft};
//    QList<glm::vec3> vertices2 = {bottomRight, topRight, topLeft};
//    navMesh->addTriangle(vertices1);
//    navMesh->addTriangle(vertices2);
}

void NavmeshTest::testTwoByTwo(){

    std::shared_ptr<NavigationMesh> navMesh = std::make_shared<NavigationMesh>();
    addSquare(navMesh, glm::vec3(0));
    addSquare(navMesh, glm::vec3(0, 0, -1));
//    addSquare(navMesh, glm::vec3(1, 0, 0));
//    addSquare(navMesh, glm::vec3(1, 0, -1));
    glm::vec3 start =glm::vec3(.1, 0, -.1);
    glm::vec3 end = glm::vec3(.9, 0, -1.9);
    QList<glm::vec3> path = navMesh->navigate(start, end);

    float totalLength = 0;
    for(int i = 0; i < path.length()-1; i ++){
        totalLength += glm::distance(path.at(i+1), path.at(i));
    }
    std::cout << "totalLength: " << totalLength << std::endl;
    for(glm::vec3 vec : path){
        std::cout << vec << std::endl;
    }

    addSquare(navMesh, glm::vec3(1, 0, 0));
    addSquare(navMesh, glm::vec3(1, 0, -1));
    path = navMesh->navigate(start, end);
    totalLength = 0;
    for(int i = 0; i < path.length()-1; i ++){
        totalLength += glm::distance(path.at(i+1), path.at(i));
    }
    std::cout << "totalLength: " << totalLength << std::endl;
    for(glm::vec3 vec : path){
        std::cout << vec << std::endl;
    }

}



void NavmeshTest::testInDifferentTriangle(){
//    QList<glm::vec3> vertices1 = {glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1)};
//    QList<glm::vec3> vertices2 = {glm::vec3(1, 0, 0), glm::vec3(1, 0, -1), glm::vec3(0, 0, -1)};
//    std::shared_ptr<NavigationMesh> navMesh = std::make_shared<NavigationMesh>();
//    navMesh->addTriangle(vertices1);
//    navMesh->addTriangle(vertices2);
//    glm::vec3 start =glm::vec3(.1, 0, -.1);
//    glm::vec3 end = glm::vec3(.9, 0, -.9);
//    glm::vec3 expectedMidpoint = glm::vec3(.5, 0, -.5);
//    QList<glm::vec3> path = navMesh->navigate(start, end);

//    assert(path.size() == 3);
//    assert(NavigationMesh::verticesNearlyEqual(start, path.at(0)));
//    assert(NavigationMesh::verticesNearlyEqual(expectedMidpoint, path.at(1)));
//    assert(NavigationMesh::verticesNearlyEqual(end, path.at(2)));


}
