#ifndef ASTARTEST_H
#define ASTARTEST_H

#include "engine/util/CommonIncludes.h"
#include <QList>


class TestVertex;
class TestEdge;

class AStarTest
{
public:
    AStarTest();
    void runTests();
    static float heuristic(std::shared_ptr<TestVertex> v1);

private:
    //tests
    void basicTest();
    void longerPathTest();
    void multiplePathsTest();
    void circularTest();
    void lambdaTest();
    void test(std::function<bool(int)> f_test);

    //helpers
    void printPath( QList<std::shared_ptr<TestVertex>> path);
    void makeAndAddEdge(std::shared_ptr<TestVertex> from, std::shared_ptr<TestVertex> to, float weight);
};

#endif // ASTARTEST_H
