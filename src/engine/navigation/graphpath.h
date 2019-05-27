#ifndef GRAPHPATH_H
#define GRAPHPATH_H

#include "engine/util/CommonIncludes.h"
#include <QList>

template <class V, class E>
class GraphPath
{
public:
    GraphPath(QList<std::shared_ptr<E>> edges)
        : m_edges(edges){
        assert(isValidPath());
    }

    std::shared_ptr<V> getVertex(int index){
        if(index < 0 || index > m_edges.size()){
            std::cout << "vertex index out of bounds in graphpath" << std::endl;
            throw -1;
        }
        if(index == m_edges.size()){
            return m_edges.at(index-1)->getVertexTo();
        }
        return m_edges.at(index)->getVertexFrom();
    }

    std::shared_ptr<E> getEdge(int index){
        if(index < 0 || index >= m_edges.size()){
            std::cout << "edge index out of bounds in graphpath" << std::endl;
            throw -1;
        }
        return m_edges.at(index);
    }

    inline float getTotalLength(){
        float length = 0;
        for(std::shared_ptr<E> edge : m_edges){
            length += edge->getWeight();
        }
        return length;
    }

    inline bool isValidPath(){
        //std::cout << "checking is valid path: " << m_edges.size() << std::endl;

        for(int i = 1; i < m_edges.size(); i ++){
            if(m_edges.at(i-1)->getVertexTo() != m_edges.at(i)->getVertexFrom()){
                std::cout << "failing at index: " << i << std::endl;
                return false;
            }
        }
        return true;
    }

    inline int getNumVertex(){
        if(m_edges.isEmpty()){
            return 0;
        }
        return m_edges.size()+1;

    }
    inline int getNumEdges(){
        return m_edges.size();
    }
    inline bool isEmpty(){
        return m_edges.isEmpty();
    }

private:
    QList<std::shared_ptr<E>> m_edges;
};

#endif // GRAPHPATH_H
