#ifndef CHUNKCULLER_H
#define CHUNKCULLER_H

#include "culler.h"
class TransformComponent;

class ChunkCuller : public Culler
{
public:
    ChunkCuller(std::shared_ptr<TransformComponent> transform);

    // Culler interface
    static const QList<glm::vec3>& getMultipliers(){
        static QList<glm::vec3> mulipliers = { glm::vec3(0, 0, 0),
                                               glm::vec3(0, 0, 1),
                                               glm::vec3(0, 1, 0),
                                               glm::vec3(0, 1, 1),
                                               glm::vec3(1, 0, 0),
                                               glm::vec3(1, 0, 1),
                                               glm::vec3(1, 1, 0),
                                               glm::vec3(1, 1, 1)};
        return mulipliers;
    }
public:
    bool shouldCull(QList<glm::vec4> &planes) override;

private:

    QList<glm::vec4> getCorners();
};

#endif // CHUNKCULLER_H
