#ifndef ASTAR_H
#define ASTAR_H


#include <QList>
#include <QMap>
#include <QSet>
#include <functional>

#include "engine/util/CommonIncludes.h"
#include "graphpath.h"
#include "vertex.h"
#include "edge.h"

//used wiki pseudocode
//https://en.wikipedia.org/wiki/A*_search_algorithm

class AStar
{
public:
    AStar();

    template <class V>
    static std::shared_ptr<V> findSmallest(QSet<std::shared_ptr<V>> openSet,
                                           QMap<std::shared_ptr<V>, float> fScore)
    {
        //std::cout << "finding smallest in set" << std::endl;
        assert(!openSet.isEmpty());
        auto i = openSet.begin();
        std::shared_ptr<V> bestVertex = *i;
        float bestVertexValue = getVertexScore(bestVertex, fScore);
        for(i; i != openSet.end(); ++i){
            float newVertexValue = getVertexScore(*i, fScore);
            if(newVertexValue < bestVertexValue){
                bestVertexValue = newVertexValue;
                bestVertex = *i;
            }
        }
        //std::cout << "returning vertex with guess: " << bestVertexValue << std::endl;
        return bestVertex;

}

    template<class V>
    static float getVertexScore(std::shared_ptr<V> vertex, QMap<std::shared_ptr<V>, float> score){
        if(score.contains(vertex)){
            return score.value(vertex);
        }
        return std::numeric_limits<float>::infinity();
    }

    template<class V, class E>
    static std::shared_ptr<GraphPath<V, E>> reconstructPath(QMap<std::shared_ptr<V>, std::shared_ptr<E>> cameFrom,std::shared_ptr<V> final){
        //std::cout << "reconstructingpath. cameFrom: " << cameFrom.size() << std::endl;
        QList<std::shared_ptr<E>> path;
        std::shared_ptr<V> current = final;
        while(cameFrom.contains(current)){
            path.prepend(cameFrom.value(current));
            current = cameFrom.value(current)->getVertexFrom();
        }
        return std::make_shared<GraphPath<V, E>>(path);
    }

    /**
     * Full function.
     * Arguments:
     * start- Starting vertex
     * f_isEnd- a function that determines whether a vertex is the end.
     * This function should return true if a given vertex is the end, and false otherwise
     * f_heuristic- a heuristic that takes in a vertex and returns how "close" it is to the end
     * note that this heuristic doesn't take in the end node.
     */
    template <class V, class E>
    static std::shared_ptr<GraphPath<V, E> > findPath(std::shared_ptr<V> start,
                                                     std::function<bool(std::shared_ptr<V>)> f_isEnd,
                                                     std::function<float(std::shared_ptr<V>)> f_heuristic){
        QSet<std::shared_ptr<V>> closedSet;
        QSet<std::shared_ptr<V>> openSet;
        QMap<std::shared_ptr<V>, std::shared_ptr<E>> cameFrom;

        QMap<std::shared_ptr<V>, float> gScore;
        gScore.insert(start, 0);
        QMap<std::shared_ptr<V>, float> fScore;
        fScore.insert(start, f_heuristic(start));
        openSet.insert(start);
        assert(openSet.contains(start));


        while(!openSet.isEmpty()){
            std::shared_ptr<V> current = findSmallest(openSet, fScore);
            //std::cout << "current: " << current->getName() << std::endl;
           if(f_isEnd(current)){
               return reconstructPath(cameFrom, current);
           }
           openSet.remove(current);
           closedSet.insert(current);
           for(std::shared_ptr<E> edge : current->getEdges()){
              // std::cout << "found edge with weight: " << edge->getWeight() << std::endl;
               std::shared_ptr<V> neighbor = edge->getVertexTo();
               if(!closedSet.contains(neighbor)){
                    float tentative_gScore = getVertexScore(current, gScore) + edge->getWeight();
                    if(!openSet.contains(neighbor)){
                        openSet.insert(neighbor);
                    }
                    else if(tentative_gScore >= getVertexScore(neighbor, gScore)){
                       continue;
                   }
                   cameFrom.insert(neighbor, edge);
                   gScore.insert(neighbor, tentative_gScore);
                   fScore.insert(neighbor, getVertexScore(neighbor, gScore) + f_heuristic(neighbor));

               }
           }
        }
        //did not find path
        QList<std::shared_ptr<E>> path;
        return std::make_shared<GraphPath<V, E>>(path);
    }

    template <class V, class E>
    static std::shared_ptr<GraphPath<V, E> > findPath(std::shared_ptr<V> start, std::shared_ptr<V> end,
                                              std::function<float(std::shared_ptr<V>)> f_heuristic)
    {
        auto lambda = [end](std::shared_ptr<V> vertex) {
            return vertex == end;
        };


        return findPath<V, E>(start, lambda, f_heuristic);
    }

    template<class V, class E>
    static float defaultHeuristic(std::shared_ptr<V> vertex){
        return 0;
    }

    template <class V, class E>
    static std::shared_ptr<GraphPath<V, E> > findPath(std::shared_ptr<V> start, std::shared_ptr<V> end){
//        auto lambda = [](std::shared_ptr<V> vertex){
//            return 0;
//        };
        return findPath<V, E>(start, end, defaultHeuristic<V, E>);
    }

    template <class V, class E>
    static std::shared_ptr<GraphPath<V, E> > findPath(std::shared_ptr<V> start, std::function<bool (std::shared_ptr<V>)> f_isEnd){
        return findPath<V, E>(start, f_isEnd, defaultHeuristic<V, E>);
    }
};




#endif // ASTAR_H



