#ifndef EDGE_H
#define EDGE_H

#include "engine/util/CommonIncludes.h"


template <typename TVertex>
class Edge
{
public:
    virtual std::shared_ptr<TVertex> getVertexFrom() = 0;
    virtual std::shared_ptr<TVertex> getVertexTo() = 0;
    virtual float getWeight() = 0;
};

#endif // EDGE_H
