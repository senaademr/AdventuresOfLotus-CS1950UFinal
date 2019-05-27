#ifndef TRIANGLEMESHTERRAINGENERATOR_H
#define TRIANGLEMESHTERRAINGENERATOR_H

#include <memory>
#include "glm/glm.hpp"
#include <QList>
#include "engine/map_generation/valuenoise.h"

class GameObject;
class CompoundNoise;
class Shape;
class NavigationPolygon;
class TextureAtlas;
class EnvironmentTexture;
class Triangle;

class TriangleMeshTerrainGenerator
{
public:
    TriangleMeshTerrainGenerator(std::shared_ptr<CompoundNoise> noise, std::shared_ptr<TextureAtlas> atlas, std::shared_ptr<EnvironmentTexture> environmentTextures);
    ~TriangleMeshTerrainGenerator();
    std::shared_ptr<Shape> makeShape(const glm::vec3 &topLeft, float dimension, int density);
    std::shared_ptr<GameObject> makeTriangleMesh(const glm::vec3 &topLeft, float dimension, float density);

private:
    QList<std::shared_ptr<NavigationPolygon> > getNavTriangles(const glm::vec3 &topLeft, float dimension , QList<std::shared_ptr<Triangle> > &collisionTriangles);
    void connectTriangles(QList<std::shared_ptr<NavigationPolygon> > &triangles, int dimension);

    glm::vec2 getTexCoords(glm::vec3 topLeft, glm::vec3 pos, std::string textureName);
    glm::vec3 findNormal(const glm::vec3 &vertex, float stepSize);
    glm::vec3 findTriangleNormal(const glm::vec3 vertex1, const glm::vec3 vertex2, const glm::vec3 vertex3);
private:

    std::shared_ptr<CompoundNoise> m_noise;
    std::shared_ptr<TextureAtlas> m_atlas;
    std::shared_ptr<EnvironmentTexture> m_environmentTextures;

};

#endif // TRIANGLEMESHTERRAINGENERATOR_H
