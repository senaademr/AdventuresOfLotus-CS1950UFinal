#include "MeshShape.h"

#include "engine/graphics/IBO.h"
#include "engine/graphics/VBOAttribMarker.h"
#include "engine/graphics/ShaderAttribLocations.h"
#include "engine/graphics/Graphics.h"
#include "engine/Animation/mesh.h"

MeshShape::MeshShape(const std::vector<float> &positions,
                     const std::vector<float> &normals,
                     const std::vector<float> &texCoords,
                     const std::vector<Bone> &bones,
                     const std::vector<VertexBone> &vertexBones,
                     const std::vector<int> &faces,
                     const std::vector<Entry> &entries,
                     VBO::GEOMETRY_LAYOUT layout):
    m_vboTriangleLayout(layout),
    m_numVertices(0),
    m_built(false),
    m_shapeName(""),
    m_pos(0),
    m_scale(1),
    m_rotation(),
    m_entries(entries)
{
    addPositions(positions);
    addNormals(normals);
    addTextureCoordinates(texCoords);
    addBones(vertexBones);
    addFaces(faces);
}

MeshShape::MeshShape(const MeshShape &meshshape2){
    m_positions = meshshape2.m_positions;
    m_normals = meshshape2.m_normals;
    m_texCoords = meshshape2.m_texCoords;
    m_bones = meshshape2.m_bones;
    m_weights = meshshape2.m_weights;
    m_boneIDs = meshshape2.m_boneIDs;
    m_faces = meshshape2.m_faces;
    m_entries = meshshape2.m_entries;

    m_vboTriangleLayout = meshshape2.m_vboTriangleLayout;
    m_triangleLayout = meshshape2.m_triangleLayout;
    m_numVertices = meshshape2.m_numVertices;
    m_handle = meshshape2.m_handle;
    m_built = meshshape2.m_built;

    m_shapeName = meshshape2.m_shapeName;
    m_pos = meshshape2.m_pos;
    m_scale = meshshape2.m_scale;
    m_rotation = meshshape2.m_rotation;
}

MeshShape::~MeshShape(){
    glDeleteVertexArrays(1, &m_handle);
}

void MeshShape::addPosition(float x, float y, float z) {
    m_positions.push_back(x);
    m_positions.push_back(y);
    m_positions.push_back(z);
    m_numVertices++;
}

void MeshShape::addPositions(const std::vector<float> &positions) {
    for(size_t i = 0; i < positions.size(); i += 3) {
        float x = positions[i];
        float y = positions[i+1];
        float z = positions[i+2];

        addPosition(x, y, z);
    }
}

void MeshShape::addNormal(float x, float y, float z) {
    m_normals.push_back(x);
    m_normals.push_back(y);
    m_normals.push_back(z);
}

void MeshShape::addNormals(const std::vector<float> &normals) {
    for(size_t i = 0; i < normals.size(); i += 3) {
        float x = normals[i];
        float y = normals[i+1];
        float z = normals[i+2];

        addNormal(x, y, z);
    }
}

void MeshShape::addTextureCoordinate(float s, float t) {
    m_texCoords.push_back(s);
    m_texCoords.push_back(t);
}

void MeshShape::addTextureCoordinates(const std::vector<float> &texCoords) {
    for(size_t i = 0; i < texCoords.size(); i += 2) {
        float s = texCoords[i];
        float t = texCoords[i+1];

        addTextureCoordinate(s, t);
    }
}

void MeshShape::addBone(VertexBone b) {
    m_weights.push_back(b.weight[0]);
    m_weights.push_back(b.weight[1]);
    m_weights.push_back(b.weight[2]);
    m_weights.push_back(b.weight[3]);

    m_boneIDs.push_back(b.id[0]);
    m_boneIDs.push_back(b.id[1]);
    m_boneIDs.push_back(b.id[2]);
    m_boneIDs.push_back(b.id[3]);

}

void MeshShape::addBones(const std::vector<VertexBone> &bones) {
    for(size_t i = 0; i < bones.size(); i++) {
        addBone(bones[i]);
    }
}

void MeshShape::addFace(int v1, int v2, int v3) {
    m_faces.push_back(v1);
    m_faces.push_back(v2);
    m_faces.push_back(v3);

}

void MeshShape::addFaces(const std::vector<int> &faces) {
    for(size_t i = 0; i < faces.size(); i += 3) {
        int v1 = faces[i];
        int v2 = faces[i+1];
        int v3 = faces[i+2];

        addFace(v1, v2, v3);
    }
}

void MeshShape::build(){
    // VBOs
    std::vector<VBOAttribMarker> posMarkers;
    posMarkers.push_back(VBOAttribMarker(ShaderAttrib::POSITION, 3, 0));
    VBO posVBO(m_positions.data(), m_positions.size(), posMarkers, m_vboTriangleLayout);

    std::vector<VBOAttribMarker> normalMarkers;
    normalMarkers.push_back(VBOAttribMarker(ShaderAttrib::NORMAL, 3, 0));
    VBO normalVBO(m_normals.data(), m_normals.size(), normalMarkers, m_vboTriangleLayout);

    std::vector<VBOAttribMarker> texMarkers;
    texMarkers.push_back(VBOAttribMarker(ShaderAttrib::TANGENT, 2, 0));
    VBO texVBO(m_texCoords.data(), m_texCoords.size(), texMarkers, m_vboTriangleLayout);

    std::vector<VBOAttribMarker> weightMarkers;
    weightMarkers.push_back(VBOAttribMarker(ShaderAttrib::COLOR, 4, 0));
    VBO weightVBO(m_weights.data(), m_weights.size(), weightMarkers, m_vboTriangleLayout);

    std::vector<VBOAttribMarker> idMarkers;
    idMarkers.push_back(VBOAttribMarker(ShaderAttrib::BINORMAL, 4, 0, VBOAttribMarker::DATA_TYPE::INT));
    VBO idVBO(m_boneIDs.data(), m_boneIDs.size(), idMarkers, m_vboTriangleLayout);

    IBO ibo(m_faces.data(), m_faces.size());

    // VAO
    glGenVertexArrays(1, &m_handle);
    glBindVertexArray(m_handle);

    posVBO.bindAndEnable();
    normalVBO.bindAndEnable();
    texVBO.bindAndEnable();
    weightVBO.bindAndEnable();
    idVBO.bindAndEnable();

    ibo.bind();

    glBindVertexArray(0);

    posVBO.unbind();
    normalVBO.unbind();
    texVBO.unbind();
    weightVBO.unbind();
    idVBO.unbind();
    ibo.unbind();

    // Triangle layout
    m_triangleLayout = posVBO.triangleLayout();

    m_numVertices = m_faces.size();

    // Has been built
    m_built = true;

    // Cleanup
//    m_positions.clear();
//    m_normals.clear();
//    m_texCoords.clear();
//    m_bones.clear();
//    m_weights.clear();
//    m_boneIDs.clear();
//    m_faces.clear();
}

glm::mat4 MeshShape::getModelMatrix() {
    glm::mat4 model;
    model = glm::translate(model, m_pos);
    model = model * glm::toMat4(m_rotation);
    model = glm::scale(model, m_scale);
    return model;
}

void MeshShape::draw(const std::shared_ptr<Graphics> &g) {
    draw(g.get());
}

void MeshShape::draw(Graphics *g) {
    // Build VAO if not buildt already
    if(!m_built) {
        build();
    }

    // Set transform
    glm::mat4 lastTransform = g->getTransform();
    g->pushTransform(getModelMatrix());

    // Draw
    glBindVertexArray(m_handle);
    for(int i=0; i<m_entries.size(); i++){
        glDrawElementsBaseVertex(m_triangleLayout, m_entries[i].numberOfIndices, GL_UNSIGNED_INT, (void*)(sizeof(uint) * m_entries[i].baseIndex), m_entries[i].baseVertex);
    }
    glBindVertexArray(0);


    // Reset transform
    g->setTransform(lastTransform);
}
