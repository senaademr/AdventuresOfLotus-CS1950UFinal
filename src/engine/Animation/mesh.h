#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <map>
#include "engine/util/CommonIncludes.h"
#include <assimp/types.h>
#include "engine/graphics/MeshShape.h"
#include "assimp/Importer.hpp"


struct Bone{
    aiMatrix4x4 offset;
    aiMatrix4x4 transformation;
};

struct VertexBone{
    glm::ivec4 id = glm::ivec4(0);
    glm::vec4 weight = glm::vec4(0.0);
};

struct Entry{
    int numberOfIndices = 0;
    int baseVertex = 0;
    int baseIndex = 0;
};

class aiMesh;
class aiNodeAnim;
class aiNode;
struct aiScene;

class Mesh
{
public:
    Mesh();
    Mesh(const Mesh &mesh2);
    void loadMesh(std::string& filename);
    void loadBones(int meshIndex, const aiMesh* pMesh);
    void transformBones(float time, std::vector<aiMatrix4x4> &transformations);
    void calculateNodeTransform(float seconds, const aiNode* node, const aiMatrix4x4& transform);

    void calculateInterpolationRotation(aiQuaternion& out, float seconds, const aiNodeAnim* animationNode);
    void calculateInterpolationPosition(aiVector3D& out, float seconds, const aiNodeAnim* animationNode);
    void calculateInterpolationScale(aiVector3D& out, float seconds, const aiNodeAnim* animationNode);


    int findRotation(float seconds, const aiNodeAnim* animationNode);
    int findPosition(float seconds, const aiNodeAnim* animationNode);
    int findScale(float seconds, const aiNodeAnim* animationNode);

    void loadAnimationMap(int index, float &count);
    void addAnimation(std::string name, float speed, float duration, float offset, float repeat);
    void updateAnimation(int index, float speed, int repeat);
    void setCurrentAnimation(std::string name, float &count);

    std::shared_ptr<MeshShape>& getShape();

private:
    std::vector<Bone> m_bones;
    std::vector<Entry> m_entries;
    std::vector<VertexBone> m_vertexBones;

    // x = speed, y = duration, z = offset, w = repeat 0 /no repeat 1
    std::map<std::string, glm::vec4> m_animationMap;
    std::string m_currentAnimation = "";


    Assimp::Importer m_importer;
    std::map<std::string, int> m_boneMap;
    std::map<std::string, aiNodeAnim*> m_nodeAnimations;
    //key int = animationIndex, value int 1 = repeat or not, value int 2 = animation speed
    // 0 repeat/no repeat 1
    std::map<int, std::pair<int, float>> m_indexMap;
    const aiScene* m_scene;
    aiMatrix4x4 m_globalTransform;
    std::shared_ptr<MeshShape> m_shape;
    int m_numberOfVertices = 0;
    int m_numberOfBones = 0;
    int m_animationIndex = 0;
    int m_cyclecount = 0;


    void addVertexBoneData(int vertexID, int boneID, float weight);
};

#endif // MESH_H
