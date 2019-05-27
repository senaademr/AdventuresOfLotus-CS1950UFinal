#ifndef TRIANGLEMESHCACHE_H
#define TRIANGLEMESHCACHE_H

#include "engine/util/CommonIncludes.h"
#include <QList>

class NoiseFunction;

class TriangleMeshCache
{
public:
    TriangleMeshCache(std::shared_ptr<NoiseFunction> noise, const glm::vec3 &topLeft, int dimension, float density);
    glm::vec3 getVertex(int col, int row);
    glm::vec3 getNormal(int col, int row);
    void nextRow();


private:
    void generateStartingRows();
    void generateStartingNormals();
    void generateStartingTexCoords();

    void generateNormal(std::shared_ptr<QList<glm::vec3>> rowVector, QList<glm::vec3> &normals, int row);

    std::shared_ptr<QList<glm::vec3>> generateRow(int row);

    glm::vec3 findNormal(glm::vec3 vertex, int col, int row);
    glm::vec3 findTriangleNormal(const glm::vec3 vertex1, const glm::vec3 vertex2, const glm::vec3 vertex3);


private:
    QList<std::shared_ptr<QList<glm::vec3>>> m_rows;
    QList<glm::vec3> m_normalsTop;
    QList<glm::vec3> m_normalsBottom;

    std::shared_ptr<NoiseFunction> m_noise;
    int m_octaves;
    glm::vec3 m_topLeft;
    float m_dimension;
    int m_density;
    int m_currentTopRow;
};

#endif // TRIANGLEMESHCACHE_H
