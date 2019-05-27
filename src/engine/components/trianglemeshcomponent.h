#ifndef TRIANGLEMESHCOMPONENT_H
#define TRIANGLEMESHCOMPONENT_H

#include "component.h"
#include <QList>

class Triangle;


class TriangleMeshComponent : public Component
{
public:
    TriangleMeshComponent(QList<std::shared_ptr<Triangle>> &collisionTriangles);
    ~TriangleMeshComponent() override {}
    QList<std::shared_ptr<Triangle> >& getCollisionTriangles();


private:
    QList<std::shared_ptr<Triangle>> m_collisionTriangles;
};

#endif // TRIANGLEMESHCOMPONENT_H
