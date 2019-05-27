#include "astartest.h"

#include "engine/navigation/astar.h"
#include "engine/navigation/graphpath.h"
#include "testvertex.h"
#include "testedge.h"

AStarTest::AStarTest(){

}

void AStarTest::runTests(){
    std::cout << "running tests" << std::endl;

    basicTest();
    longerPathTest();
    multiplePathsTest();
    circularTest();
    lambdaTest();
    std::cout << "passed all tests" << std::endl;
}

float AStarTest::heuristic(std::shared_ptr<TestVertex> v1){
    return 0;
}


void AStarTest::basicTest(){

    std::shared_ptr<TestVertex> v1 = std::make_shared<TestVertex>("A");
    std::shared_ptr<TestVertex> v2 = std::make_shared<TestVertex>("B");
    makeAndAddEdge(v1, v2, 1);
    std::function<float(std::shared_ptr<TestVertex>)> f = heuristic;
    std::shared_ptr<GraphPath<TestVertex, TestEdge>> path = AStar::findPath<TestVertex, TestEdge>(v1, v2);
    //printPath(path);

    assert(path->getNumEdges() == 1);
    assert(path->getEdge(0)->getVertexFrom()->getName().compare("A") == 0);
    assert(path->getEdge(0)->getVertexTo()->getName().compare("B") == 0);
}

void AStarTest::longerPathTest(){
    std::shared_ptr<TestVertex> v1 = std::make_shared<TestVertex>("A");
    std::shared_ptr<TestVertex> v2 = std::make_shared<TestVertex>("B");
    std::shared_ptr<TestVertex> v3 = std::make_shared<TestVertex>("C");
    std::shared_ptr<TestVertex> v4 = std::make_shared<TestVertex>("D");
    makeAndAddEdge(v1, v2, 1);
    makeAndAddEdge(v2, v3, 1);
    makeAndAddEdge(v3, v4, 1);

    std::function<float(std::shared_ptr<TestVertex>)> f = heuristic;
    std::shared_ptr<GraphPath<TestVertex, TestEdge>> path = AStar::findPath<TestVertex, TestEdge>(v1, v4);

    assert(path->getNumEdges() == 3);
    assert(path->getEdge(0)->getVertexFrom()->getName().compare("A") == 0);
    assert(path->getEdge(0)->getVertexTo()->getName().compare("B") == 0);

    assert(path->getEdge(1)->getVertexFrom()->getName().compare("B") == 0);
    assert(path->getEdge(1)->getVertexTo()->getName().compare("C") == 0);

    assert(path->getEdge(2)->getVertexFrom()->getName().compare("C") == 0);
    assert(path->getEdge(2)->getVertexTo()->getName().compare("D") == 0);
}

void AStarTest::multiplePathsTest(){
    std::shared_ptr<TestVertex> v1 = std::make_shared<TestVertex>("A");
    std::shared_ptr<TestVertex> v2 = std::make_shared<TestVertex>("B");
    std::shared_ptr<TestVertex> v3 = std::make_shared<TestVertex>("C");
    std::shared_ptr<TestVertex> v4 = std::make_shared<TestVertex>("D");
    makeAndAddEdge(v1, v2, 1);
    makeAndAddEdge(v1, v3, 3);
    makeAndAddEdge(v3, v4, 2);
    makeAndAddEdge(v2, v4, 6);
    std::function<float(std::shared_ptr<TestVertex>)> f = heuristic;
    std::shared_ptr<GraphPath<TestVertex, TestEdge>> path = AStar::findPath<TestVertex, TestEdge>(v1, v4, f);
    //printPath(path);
    assert(path->getNumEdges() == 2);
    assert(path->getEdge(0)->getVertexFrom()->getName().compare("A") == 0);
    assert(path->getEdge(0)->getVertexTo()->getName().compare("C") == 0);

    assert(path->getEdge(1)->getVertexFrom()->getName().compare("C") == 0);
    assert(path->getEdge(1)->getVertexTo()->getName().compare("D") == 0);

}

void AStarTest::circularTest(){
    std::shared_ptr<TestVertex> v1 = std::make_shared<TestVertex>("A");
    std::shared_ptr<TestVertex> v2 = std::make_shared<TestVertex>("B");
    std::shared_ptr<TestVertex> v3 = std::make_shared<TestVertex>("C");
    std::shared_ptr<TestVertex> v4 = std::make_shared<TestVertex>("D");
    std::shared_ptr<TestVertex> v5 = std::make_shared<TestVertex>("E");
    makeAndAddEdge(v1, v2, 1);
    makeAndAddEdge(v2, v1, 0);

    makeAndAddEdge(v1, v3, 3);
    makeAndAddEdge(v2, v3, 1);

    makeAndAddEdge(v1, v4, 6);
    makeAndAddEdge(v1, v5, 20);

    makeAndAddEdge(v3, v4, 2);
    makeAndAddEdge(v4, v5, 5);
    std::function<float(std::shared_ptr<TestVertex>)> f = heuristic;
    std::shared_ptr<GraphPath<TestVertex, TestEdge>> path = AStar::findPath<TestVertex, TestEdge>(v1, v5, f);
    //printPath(path);
    assert(path->getNumEdges() == 4);
    assert(path->getEdge(0)->getVertexFrom()->getName().compare("A") == 0);
    assert(path->getEdge(0)->getVertexTo()->getName().compare("B") == 0);

    assert(path->getEdge(1)->getVertexFrom()->getName().compare("B") == 0);
    assert(path->getEdge(1)->getVertexTo()->getName().compare("C") == 0);
    assert(path->getEdge(2)->getVertexFrom()->getName().compare("C") == 0);
    assert(path->getEdge(2)->getVertexTo()->getName().compare("D") == 0);
    assert(path->getEdge(3)->getVertexFrom()->getName().compare("D") == 0);
    assert(path->getEdge(3)->getVertexTo()->getName().compare("E") == 0);


}

void AStarTest::test(std::function<bool(int)> f_test){
    //std::cout << "running this" << std::endl;
    assert(f_test(5));
}


void AStarTest::lambdaTest(){

    int i = 5;
    auto lambda = [i](int a){
        return a == 5;
    };
    //std::cout << lambda(5) << ", " << lambda(7) << std::endl;
    test(lambda);
}

void AStarTest::makeAndAddEdge(std::shared_ptr<TestVertex> from, std::shared_ptr<TestVertex> to, float weight){
    std::shared_ptr<TestEdge> e = std::make_shared<TestEdge>(from, to, weight);
    from->addEdge(e);
}

void AStarTest::printPath( QList<std::shared_ptr<TestVertex>> path){
    std::cout << "printing path: " << std::endl;
    for(std::shared_ptr<TestVertex> vertex : path){
        std::cout << vertex->getName() << std::endl;
    }
}
