#ifndef MESHSHAPE_H
#define MESHSHAPE_H

#include "engine/util/CommonIncludes.h"
#include "VBO.h"
#include "Shape.h"

#include <vector>
#include <memory>

struct Bone;
struct VertexBone;
class Graphics;
struct Entry;

class MeshShape : public Shape
{
public:
    MeshShape(const std::vector<float> &positions,
              const std::vector<float> &normals,
              const std::vector<float> &texCoords,
              const std::vector<Bone> &bones,
              const std::vector<VertexBone> &vertexBones,
              const std::vector<int> &faces,
              const std::vector<Entry> &entries,
              VBO::GEOMETRY_LAYOUT layout=VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES);

    MeshShape(const MeshShape &meshshape2);
    ~MeshShape();

    void addPosition(float x, float y, float z);
    void addPositions(const std::vector<float> &positions);

    void addNormal(float x, float y, float z);
    void addNormals(const std::vector<float> &normals);

    void addTextureCoordinate(float s, float t);
    void addTextureCoordinates(const std::vector<float> &texCoords);

    void addBone(VertexBone b);
    void addBones(const std::vector<VertexBone> &bones);

    void addFace(int v1, int v2, int v3);
    void addFaces(const std::vector<int> &faces);

    void draw(const std::shared_ptr<Graphics> &g);
    void draw(Graphics *g);

    glm::mat4 getModelMatrix();

private:
    void build();
    std::vector<float> m_positions;
    std::vector<float> m_normals;
    std::vector<float> m_texCoords;
    std::vector<Bone> m_bones;
    std::vector<float> m_weights;
    std::vector<int> m_boneIDs;
    std::vector<int> m_faces;
    std::vector<Entry> m_entries;

    VBO::GEOMETRY_LAYOUT m_vboTriangleLayout;
    GLenum m_triangleLayout;
    GLuint m_numVertices;
    GLuint m_handle;
    bool m_built;

    friend class Graphics;

    std::string m_shapeName;
    glm::vec3 m_pos;
    glm::vec3 m_scale;
    glm::quat m_rotation;
};

#endif // MESHSHAPE_H
