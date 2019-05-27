#include "navigationpolygon.h"

#include "engine/navigation/navigationedge.h"

NavigationPolygon::NavigationPolygon(){

}

void NavigationPolygon::addEdge(std::shared_ptr<NavigationEdge> edge){
    m_edges.append(edge);

}
void NavigationPolygon::removeEdge(std::shared_ptr<NavigationEdge> edge){
    m_edges.removeOne(edge);
}

void NavigationPolygon::removeNeighbor(std::shared_ptr<NavigationPolygon> neighbor){
    for(std::shared_ptr<NavigationEdge> edge : m_edges){
        if(edge->getVertexTo() == neighbor){
            //std::cout << "removing neighbor" << std::endl;
            removeEdge(edge);
            return;
        }
    }
    std::cout << "Warning: tried to a neighbor that did not exist" << std::endl;

}

QList<std::shared_ptr<NavigationEdge> > NavigationPolygon::getEdges(){
    QList<std::shared_ptr<NavigationEdge>> result;
    for(std::shared_ptr<NavigationEdge> edge : m_edges){
        if(edge->getVertexTo()->isAccessable()){
            result.append(edge);
        }
    }
    return result;

}
