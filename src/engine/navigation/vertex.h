#ifndef VERTEX_H
#define VERTEX_H

#include "engine/util/CommonIncludes.h"
#include <QList>

template <typename TEdge>
class Vertex
{
public:
    virtual QList<std::shared_ptr<TEdge>> getEdges() = 0;

};

template <typename TEdge>
inline uint qHash(const std::shared_ptr<Vertex<TEdge>> &v){
    std::cout << "in vertex  " << v.get() << std::endl;
    return qHash((v.get()));
}

//template <typename TEdge>
//uint qHash(const std::shared_ptr<Vertex<TEdge>> &v){
//    return 2;
//    //return qHash(*(v.get()));
//}


//template <typename TEdge>
//inline uint qHash(const Vertex<TEdge> &v){
//    return qHash(&v);
//}

//template <typename TEdge>
//inline bool operator==(const Vertex<TEdge> &v1, const Vertex<TEdge> &v2)
//{
//    return &v1 == &v2;
//}


//template <typename TEdge>
//inline bool operator==(const std::shared_ptr<Vertex<TEdge>> &v1, const std::shared_ptr<Vertex<TEdge>> &v2)
//{
//    return *(v1.get()) == *(v2.get());
//}

#endif // VERTEX_H
