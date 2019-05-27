#include "trianglemeshterraingenerator.h"
#include "engine/basics/gameobject.h"

#include "engine/map_generation/valuenoise.h"
#include "engine/graphics/Shape.h"
#include "engine/components/objectdrawcomponent.h"
#include "engine/components/transformcomponent.h"
#include "engine/components/trianglemeshcomponent.h"
#include "engine/navigation/navigationtriangle.h"
#include "engine/map/shapevertex.h"
#include "trianglemeshcache.h"
#include "final/final_components/terrain_components/trianglemeshterraincomponent.h"
#include "engine/map/textureatlas.h"

#include "engine/map_generation/compoundnoise.h"
#include "engine/collisionutils/triangle.h"

TriangleMeshTerrainGenerator::TriangleMeshTerrainGenerator(std::shared_ptr<CompoundNoise> noise, std::shared_ptr<TextureAtlas> atlas
                                                           , std::shared_ptr<EnvironmentTexture> environmentTextures)
    : m_noise(noise),
      m_atlas(atlas),
      m_environmentTextures(environmentTextures)
{

}

TriangleMeshTerrainGenerator::~TriangleMeshTerrainGenerator()
{

}

std::shared_ptr<Shape> TriangleMeshTerrainGenerator::makeShape(const glm::vec3 &topLeft, float dimension,
                                                               int density){
    std::shared_ptr<Shape> shape = std::make_shared<Shape>();
//    shape->setLayout(VBO::LAYOUT_LINE_STRIP);
    //std::cout << "making shape" << std::endl;
    int arrayPos = 0;

    std::shared_ptr<TriangleMeshCache> triangleMeshCache
            = std::make_shared<TriangleMeshCache>(m_noise, topLeft, dimension, density);

    for(int row = 0; row < dimension *density; row ++){
        for(int col = 0; col < dimension* density; col ++){
            glm::vec3 currentTopLeft = triangleMeshCache->getVertex(col, 1);
            glm::vec3 currentTopRight = triangleMeshCache->getVertex(col+1, 1);
            glm::vec3 currentBottomLeft = triangleMeshCache->getVertex(col, 2);
            glm::vec3 currentBottomRight = triangleMeshCache->getVertex(col+1, 2);

            glm::vec3 currentTopLeftNormal = triangleMeshCache->getNormal(col, 1);
            glm::vec3 currentTopRightNormal = triangleMeshCache->getNormal(col+1, 1);
            glm::vec3 currentBottomLeftNormal = triangleMeshCache->getNormal(col, 2);
            glm::vec3 currentBottomRightNormal = triangleMeshCache->getNormal(col+1, 2);

            std::string textureName = m_noise->getTextureAtlasName(currentTopLeft);

            glm::vec2 currentTopLeftTex = getTexCoords(currentTopLeft, currentTopLeft, textureName);
            glm::vec2 currentTopRightTex = getTexCoords(currentTopLeft, currentTopRight, textureName);
            glm::vec2 currentBottomLeftTex = getTexCoords(currentTopLeft, currentBottomLeft, textureName);
            glm::vec2 currentBottomRightTex = getTexCoords(currentTopLeft, currentBottomRight, textureName);

            shape->addVertex(currentBottomLeft, currentBottomLeftNormal, currentBottomLeftTex);
            shape->addVertex(currentBottomRight, currentBottomRightNormal, currentBottomRightTex);
            shape->addVertex(currentTopLeft, currentTopLeftNormal, currentTopLeftTex);
            shape->addVertex(currentTopRight, currentTopRightNormal, currentTopRightTex);

            shape->addFace(arrayPos, arrayPos +1, arrayPos + 2);
            shape->addFace(arrayPos+1, arrayPos + 3, arrayPos + 2);

            arrayPos +=4;
        }
        triangleMeshCache->nextRow();
    }
    return shape;
}

QList<std::shared_ptr<NavigationPolygon> > TriangleMeshTerrainGenerator::getNavTriangles(const glm::vec3 &topLeft, float dimension,
                                                                                         QList<std::shared_ptr<Triangle>> &collisionTriangles){
    QList<std::shared_ptr<NavigationPolygon> > navTriangles;

    std::shared_ptr<TriangleMeshCache> triangleMeshCache
            = std::make_shared<TriangleMeshCache>(m_noise,topLeft, dimension, 1);

    for(int row = 0; row < dimension; row ++){
        for(int col = 0; col < dimension; col ++){
            glm::vec3 currentBottomLeft = triangleMeshCache->getVertex(col, 2);
            glm::vec3 currentBottomRight = triangleMeshCache->getVertex(col+1, 2);
            glm::vec3 currentTopLeft = triangleMeshCache->getVertex(col, 1);
            glm::vec3 currentTopRight = triangleMeshCache->getVertex(col+1, 1);

            std::shared_ptr<NavigationTriangle> navTriangle1
                    = std::make_shared<NavigationTriangle>(currentBottomLeft,currentBottomRight ,currentTopLeft);
            std::shared_ptr<NavigationTriangle> navTriangle2
                    = std::make_shared<NavigationTriangle>(currentBottomRight, currentTopRight, currentTopLeft);
            navTriangles.append(navTriangle1);
            navTriangles.append(navTriangle2);

            collisionTriangles.append(std::make_shared<Triangle>(currentBottomLeft, currentBottomRight, currentTopLeft));
            collisionTriangles.append(std::make_shared<Triangle>(currentBottomRight, currentTopRight, currentTopLeft));
        }
        triangleMeshCache->nextRow();
    }
    return navTriangles;
}



glm::vec2 TriangleMeshTerrainGenerator::getTexCoords(glm::vec3 topLeft, glm::vec3 pos, std::string textureName){
    float x = pos.x - std::floor(topLeft.x);
    float y = pos.z - std::floor(topLeft.z);
    glm::vec2 textureCoords = m_atlas->toTextureCoords(textureName, glm::vec2(x,y));
    return textureCoords;

}


//try using generate mipmap
//1) (where setting filter level) generate step when create texture
// 2) right after that, set filter level to GL_LINEAR_MIPMAP_NEAREST or one of the others
// current api uses same filter for both min and mag- hopefully isn't an issue?
// only care about min_filter (minification filter)
//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml
std::shared_ptr<GameObject> TriangleMeshTerrainGenerator::makeTriangleMesh(const glm::vec3 &topLeft, float dimension, float density)
{
    std::shared_ptr<GameObject> object = std::make_shared<GameObject>();

    glm::vec3 pos = glm::vec3(0);
    glm::vec3 size = glm::vec3(1);

    std::shared_ptr<TransformComponent> transformComponent
            = std::make_shared<TransformComponent>(pos, size);

    QList<std::shared_ptr<Triangle>> collisionTriangles;

    std::shared_ptr<ObjectDrawComponent> drawComponent = std::make_shared<ObjectDrawComponent>();
    std::shared_ptr<Shape> shape = makeShape(topLeft, dimension, density);
    drawComponent->setShapeType("shape");
    drawComponent->setShape(shape);
    drawComponent->setMaterial("terrain");
    QList<std::shared_ptr<NavigationPolygon> > navigationTriangles = getNavTriangles(topLeft, dimension, collisionTriangles);

    std::shared_ptr<TriangleMeshTerrainComponent> terrainInfoComponent
            = std::make_shared<TriangleMeshTerrainComponent>(navigationTriangles, topLeft, dimension);
    std::shared_ptr<TriangleMeshComponent> collisionMeshComponent
            = std::make_shared<TriangleMeshComponent>(collisionTriangles);

    object->addComponent<ObjectDrawComponent>(drawComponent);
    object->addComponent<TransformComponent>(transformComponent);
    object->addComponent<TriangleMeshTerrainComponent>(terrainInfoComponent);
    object->addComponent<TriangleMeshComponent>(collisionMeshComponent);

    return object;
}

