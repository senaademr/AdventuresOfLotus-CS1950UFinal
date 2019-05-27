#ifndef NAVMESHTEST_H
#define NAVMESHTEST_H

#include "engine/util/CommonIncludes.h"

class NavigationMesh;

class NavmeshTest
{
public:
    NavmeshTest();
    void runTests();

private:

    void testPointInTriangle();
    void test3DPointInTriangle();
    void testInSameTriangle();
    void testPointInTriangleClose();
    void testTwoByTwo();
    void testInDifferentTriangle();


    void addSquare(std::shared_ptr<NavigationMesh> navMesh, glm::vec3 bottomLeft);
};

#endif // NAVMESHTEST_H
