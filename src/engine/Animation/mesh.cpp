#include "mesh.h"
#include "assimp/postprocess.h"
#include "assimp/mesh.h"
#include "assimp/scene.h"

#include <QFile>

Mesh::Mesh()
{

}

Mesh::Mesh(const Mesh &mesh2){
    m_bones = mesh2.m_bones;
    m_entries = mesh2.m_entries;
    m_vertexBones = mesh2.m_vertexBones;
    m_animationMap = mesh2.m_animationMap;
    m_currentAnimation = mesh2.m_currentAnimation;
    m_importer = mesh2.m_importer;
    m_boneMap = mesh2.m_boneMap;
    m_nodeAnimations = mesh2.m_nodeAnimations;
    m_indexMap = mesh2.m_indexMap;
    m_scene = mesh2.m_scene;
    m_globalTransform = mesh2.m_globalTransform;
    m_shape = std::make_shared<MeshShape>(*mesh2.m_shape);
    m_numberOfVertices = mesh2.m_numberOfVertices;
    m_numberOfBones = mesh2.m_numberOfBones;
    m_animationIndex = mesh2.m_animationIndex;
    m_cyclecount = mesh2.m_cyclecount;
}

void Mesh::loadMesh(std::string& filename){
    m_scene = m_importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
    if(!m_scene){
        std::cout<<m_importer.GetErrorString()<<std::endl;
    }
    m_globalTransform=m_scene->mRootNode->mTransformation;
    m_globalTransform.Inverse();

    std::vector<float> positions;
    std::vector<float> normals;
    std::vector<float> texCoords;
    std::vector<int> faces;

    m_entries.resize(m_scene->mNumMeshes);
    int indexCount = 0;

    for(int i=0; i<m_entries.size(); i++){
        const aiMesh* currentMesh = m_scene->mMeshes[i];
        m_entries[i].numberOfIndices = currentMesh->mNumFaces*3;
        m_entries[i].baseVertex = m_numberOfVertices;
        m_entries[i].baseIndex = indexCount;

        m_numberOfVertices += currentMesh->mNumVertices;
        indexCount += m_entries[i].numberOfIndices;
    }

    positions.reserve(m_numberOfVertices);
    normals.reserve(m_numberOfVertices);
    texCoords.reserve(m_numberOfVertices);
    m_vertexBones.resize(m_numberOfVertices);
    faces.reserve(m_numberOfVertices);

    for(int i=0; i<m_entries.size(); i++){
        const aiMesh* currentMesh = m_scene->mMeshes[i];
        for(int j=0; j<currentMesh->mNumVertices; j++){
            const aiVector3D pos = currentMesh->mVertices[j];
            const aiVector3D normal = currentMesh->mNormals[j];
            aiVector3D texCoord(0.f, 0.f, 0.f);
            if(currentMesh->HasTextureCoords(0)){
                texCoord=currentMesh->mTextureCoords[0][j];
            }
            positions.push_back(pos.x);
            positions.push_back(pos.y);
            positions.push_back(pos.z);

            normals.push_back(normal.x);
            normals.push_back(normal.y);
            normals.push_back(normal.z);

            texCoords.push_back(texCoord.x);
            texCoords.push_back(texCoord.y);
        }
        loadBones(i, currentMesh);
        for(int k =0; k<currentMesh->mNumFaces; k++){
            const aiFace& face = currentMesh->mFaces[k];
            faces.push_back(face.mIndices[0]);
            faces.push_back(face.mIndices[1]);
            faces.push_back(face.mIndices[2]);
        }
    }
    for(int i=0; i< m_scene->mNumAnimations; i++){
        std::pair<int, float> pair = std::make_pair<int, float>(0, 1.f);
        m_indexMap.insert(std::pair<int, std::pair<int, float>>(i, pair));
    }
    float temp = 0.f;
    loadAnimationMap(0, temp);
    m_shape = std::make_shared<MeshShape>(positions, normals, texCoords, m_bones, m_vertexBones, faces, m_entries);
}

void Mesh::loadBones(int meshIndex, const aiMesh* pMesh){
    for(int i=0; i< pMesh->mNumBones; i++){
        int boneIndex = 0;
        std::string boneName(pMesh->mBones[i]->mName.data);

        if(m_boneMap.find(boneName) == m_boneMap.end()){
            boneIndex = m_numberOfBones;
            m_numberOfBones++;
            Bone current;
            current.offset= pMesh->mBones[i]->mOffsetMatrix;
            m_bones.push_back(current);
            m_boneMap.insert(std::pair<std::string, int>(boneName, boneIndex));
        } else {
            boneIndex = m_boneMap[boneName];
        }
        for(int j=0; j< pMesh->mBones[i]->mNumWeights; j++){
            int id = m_entries[meshIndex].baseVertex+pMesh->mBones[i]->mWeights[j].mVertexId;
            float weight = pMesh->mBones[i]->mWeights[j].mWeight;
            addVertexBoneData(id, boneIndex, weight);
        }
    }
}

void Mesh:: transformBones(float time, std::vector<aiMatrix4x4>& transformations){
    transformations.clear();
    float animSeconds = 0;
    //currentAnimation is used
    if(m_currentAnimation.compare("")){
        float speed = m_animationMap[m_currentAnimation].x;
        float duration = m_animationMap[m_currentAnimation].y;
        float offset = m_animationMap[m_currentAnimation].z;
        if(m_animationMap[m_currentAnimation].w > 0.f){
            if(m_cyclecount > 0.f){
                animSeconds = duration*speed;
                animSeconds /= speed;
                animSeconds += offset;
            } else {
                animSeconds = fmod(time, duration*speed);
                int anim = animSeconds;
                int dur = duration*speed;
                if(anim+1 == dur){
                    m_cyclecount++;
                }
                animSeconds /= speed;
                animSeconds += offset;
            }
        }else {
            if(duration >= 0){
                animSeconds = fmod(time, duration*speed);
                animSeconds /= speed;
                animSeconds += offset;
            }
            else{   //reverse animation
                animSeconds = fmod(time, duration*speed);
                animSeconds = -duration*speed-animSeconds;
                animSeconds /= speed;
                animSeconds += offset;
            }
        }
    }else{
        std::pair<int, float> currentAnimationInfo = m_indexMap[m_animationIndex];
        float speed = currentAnimationInfo.second;
        int repeat = currentAnimationInfo.first;
        float duration = m_scene->mAnimations[m_animationIndex]->mDuration;
        //TERRIBLE code that targets the specific animations that flash by removing the final frame of them
        if(duration == 40 || duration == 28 || duration == 22){
            duration--;
        }
//        std::cout << "Animation: duration " << duration << std::endl;
        if(repeat > 0){
            if(m_cyclecount > 0.f){
                animSeconds = duration*speed;
                animSeconds /= speed;
            } else {
                animSeconds = fmod(time, duration*speed);
                int anim = animSeconds;
                int dur = duration*speed;
                if(anim+1 == dur){
                    m_cyclecount++;
                }
                animSeconds /= speed;
            }
        }else {
            animSeconds = fmod(time, duration*speed);
            animSeconds /= speed;
        }
    }
    aiMatrix4x4 identity;
    identity = aiMatrix4x4();
    calculateNodeTransform(animSeconds, m_scene->mRootNode, identity);
    transformations.resize(m_numberOfBones);
    for(int i = 0; i<transformations.size(); i++){
        transformations[i] = m_bones[i].transformation;
    }
}

void Mesh::calculateInterpolationRotation(aiQuaternion& out, float seconds, const aiNodeAnim* animationNode){
    if(animationNode->mNumRotationKeys == 1){
        out = animationNode->mRotationKeys[0].mValue;
        return;
    }
    int rotationIndex = findRotation(seconds, animationNode);
    int nextRotationIndex = rotationIndex+1;
    if(nextRotationIndex < animationNode->mNumRotationKeys){
        float delta = animationNode->mRotationKeys[nextRotationIndex].mTime - animationNode->mRotationKeys[rotationIndex].mTime;
        float factor = (seconds-animationNode->mRotationKeys[rotationIndex].mTime)/delta;
        if(factor >= 0.f && factor <= 1.f){
            const aiQuaternion& start = animationNode->mRotationKeys[rotationIndex].mValue;
            const aiQuaternion& end = animationNode->mRotationKeys[nextRotationIndex].mValue;
            aiQuaternion::Interpolate(out, start, end, factor);
            out = out.Normalize();
        }
    }
}

void Mesh::calculateInterpolationPosition(aiVector3D& out, float seconds, const aiNodeAnim* animationNode){
    if(animationNode->mNumPositionKeys == 1){
        out = animationNode->mPositionKeys[0].mValue;
        return;
    }
    int positionIndex = findPosition(seconds, animationNode);
    int nextPositionIndex = positionIndex+1;
    if(nextPositionIndex < animationNode->mNumPositionKeys){
        float delta = animationNode->mPositionKeys[nextPositionIndex].mTime - animationNode->mPositionKeys[positionIndex].mTime;
        float factor = (seconds-animationNode->mPositionKeys[positionIndex].mTime)/delta;
        if(factor >= 0.f && factor <= 1.f){
            const aiVector3D& start = animationNode->mPositionKeys[positionIndex].mValue;
            const aiVector3D& end = animationNode->mPositionKeys[nextPositionIndex].mValue;
            aiVector3D deltaVectors = end-start;
            out = start + factor*deltaVectors;
        }
    }
}

void Mesh::calculateInterpolationScale(aiVector3D& out, float seconds, const aiNodeAnim* animationNode){
    if(animationNode->mNumScalingKeys == 1){
        out = animationNode->mScalingKeys[0].mValue;
        return;
    }
    int scaleIndex = findScale(seconds, animationNode);
    int nextScaleIndex = scaleIndex+1;
    if(nextScaleIndex < animationNode->mNumScalingKeys){
        float delta = animationNode->mScalingKeys[nextScaleIndex].mTime - animationNode->mScalingKeys[scaleIndex].mTime;
        float factor = (seconds-animationNode->mScalingKeys[scaleIndex].mTime)/delta;
        if(factor >= 0.f && factor <= 1.f){
            const aiVector3D& start = animationNode->mScalingKeys[scaleIndex].mValue;
            const aiVector3D& end = animationNode->mScalingKeys[nextScaleIndex].mValue;
            aiVector3D deltaVectors = end-start;
            out = start + factor*deltaVectors;
        }
    }
}

int Mesh::findRotation(float seconds, const aiNodeAnim* animationNode){
    if(animationNode->mNumRotationKeys > 0){
        for(int i=0; i<animationNode->mNumRotationKeys-1; i++){
            if(seconds < animationNode->mRotationKeys[i+1].mTime){
                return i;
            }
        }
    }
    return 0;
}

int Mesh::findPosition(float seconds, const aiNodeAnim* animationNode){
    if(animationNode->mNumPositionKeys > 0){
        for(int i=0; i<animationNode->mNumPositionKeys-1; i++){
            if(seconds < animationNode->mPositionKeys[i+1].mTime){
                return i;
            }
        }
    }
    return 0;
}

int Mesh::findScale(float seconds, const aiNodeAnim* animationNode){
    if(animationNode->mNumScalingKeys > 0){
        for(int i=0; i<animationNode->mNumScalingKeys-1; i++){
            if(seconds < animationNode->mScalingKeys[i+1].mTime){
                return i;
            }
        }
    }
    return 0;
}

void Mesh::calculateNodeTransform(float seconds, const aiNode* node, const aiMatrix4x4& transform){
    std::string nodeName(node->mName.data);
    aiMatrix4x4 nodeTransform(node->mTransformation);
    const aiNodeAnim* nodeAnim = m_nodeAnimations[nodeName];
    if(nodeAnim){
        //scale
        aiVector3D scale;
        calculateInterpolationScale(scale, seconds, nodeAnim);

        //rotate
        aiQuaternion rotation;
        calculateInterpolationRotation(rotation, seconds, nodeAnim);

        //translate
        aiVector3D translation;
        calculateInterpolationPosition(translation, seconds, nodeAnim);

        aiMatrix4x4 translationMatrix;
        aiMatrix4x4 scaleMatrix;
        nodeTransform = translationMatrix.Translation(translation, translationMatrix) * aiMatrix4x4(rotation.GetMatrix()) * scaleMatrix.Scaling(scale, scaleMatrix);
    }
    aiMatrix4x4 totalTransform = transform*nodeTransform;
    if(m_boneMap.find(nodeName) != m_boneMap.end()){
        int index = m_boneMap[nodeName];
        m_bones[index].transformation = m_globalTransform*totalTransform*m_bones[index].offset;
    }
    for(int i =0; i< node->mNumChildren; i++){
        calculateNodeTransform(seconds, node->mChildren[i], totalTransform);
    }
}

std::shared_ptr<MeshShape>& Mesh::getShape(){
    return m_shape;
}

void Mesh::addVertexBoneData(int vertexID, int boneID, float weight){
    for(int i=0; i<4; i++){
        if(m_vertexBones[vertexID].weight[i] == 0.0){
            m_vertexBones[vertexID].id[i] = boneID;
            m_vertexBones[vertexID].weight[i] = weight;
            return;
        }
    }
}

void Mesh::loadAnimationMap(int index, float &count){
    if(index == m_animationIndex && m_nodeAnimations.size() > 0){
        return;
    }
    if(index >= m_scene->mNumAnimations){
        index = 0;
    }
    m_animationIndex = index;
    m_cyclecount = 0;
    count = 0;
    m_nodeAnimations.clear();
    const aiAnimation* animation = m_scene->mAnimations[m_animationIndex];
    for(int i=0; i<animation->mNumChannels; i++){
        aiNodeAnim* currentNodeAnim = animation->mChannels[i];
        std::string nodeName(currentNodeAnim->mNodeName.data);
        if(m_nodeAnimations.find(nodeName) == m_nodeAnimations.end()){
            m_nodeAnimations.insert(std::pair<std::string, aiNodeAnim*>(nodeName, currentNodeAnim));
        }
    }
}

void Mesh::addAnimation(std::string name, float speed, float duration, float offset, float repeat){
//    std::cout << "name: " << name << m_animationMap.count(name) << std::endl;
    if(m_animationMap.count(name) == 1){
        m_animationMap.erase(name);
    }

    glm::vec4 entry = glm::vec4(speed, duration, offset, repeat);

    m_animationMap.insert(std::pair<std::string, glm::vec4>(name, entry));
}

void Mesh::updateAnimation(int index, float speed, int repeat){
    std::pair<int, float> pair(repeat, speed);
    m_indexMap[index] = pair;
}

void Mesh::setCurrentAnimation(std::string name, float &count){
    if(m_animationMap.find(name) != m_animationMap.end()){
        if(name.compare(m_currentAnimation)){
            m_currentAnimation = name;
            m_cyclecount = 0;
            count = 0;
        }
    }else{
        m_currentAnimation = "";
    }
}
