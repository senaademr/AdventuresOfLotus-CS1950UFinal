#include "trianglemeshcache.h"

#include "engine/map_generation/noisefunction.h"
#include "engine/util/util.h"

TriangleMeshCache::TriangleMeshCache(std::shared_ptr<NoiseFunction> noise, const glm::vec3 &topLeft, int dimension, float density)
    : m_noise(noise),
      m_topLeft(topLeft),
      m_dimension(dimension),
      m_density(density),
      m_currentTopRow(-1)
{
    generateStartingRows();
    generateStartingNormals();
    generateStartingTexCoords();
}

void TriangleMeshCache::generateStartingRows(){
    std::shared_ptr<QList<glm::vec3>> row0 = generateRow(0);
    std::shared_ptr<QList<glm::vec3>> row1 = generateRow(1);
    std::shared_ptr<QList<glm::vec3>> row2 = generateRow(2);
    std::shared_ptr<QList<glm::vec3>> row3 = generateRow(3);

    m_rows.append(row0);
    m_rows.append(row1);
    m_rows.append(row2);
    m_rows.append(row3);
}


void TriangleMeshCache::generateStartingNormals(){
    std::shared_ptr<QList<glm::vec3>> row1 = m_rows.at(1);
    std::shared_ptr<QList<glm::vec3>> row2 = m_rows.at(2);
    generateNormal(row1, m_normalsTop, 1);
    generateNormal(row2, m_normalsBottom, 2);
}

void TriangleMeshCache::generateStartingTexCoords(){

}

void TriangleMeshCache::generateNormal(std::shared_ptr<QList<glm::vec3>> rowVector, QList<glm::vec3> &normals, int row){

    for(int i = 1; i < rowVector->size()-1; i ++){
        int col = i-1;
        glm::vec3 normal = findNormal(rowVector->at(i), col, row);
        normals.append(normal);
    }
}

std::shared_ptr<QList<glm::vec3> > TriangleMeshCache::generateRow(int row){
    float row_float = static_cast<float>(row);

    std::shared_ptr<QList<glm::vec3>> rowVector = std::make_shared<QList<glm::vec3>>();
    float stepSize = 1.f/m_density;
    for(int col = -1; col < m_dimension * m_density+ 2; col ++){
        float x = stepSize* col + m_topLeft.x;
        float z0 = m_currentTopRow*stepSize + m_topLeft.z;
        rowVector->append(m_noise->interpolatedNoiseToVec(glm::vec2(x, z0 + row_float * stepSize)));
    }

    return rowVector;
}


void TriangleMeshCache::nextRow(){
    //float stepSize = 1.f/m_density;
    m_rows.removeFirst();
    m_currentTopRow ++;

    std::shared_ptr<QList<glm::vec3>> row3 = generateRow(3);
    m_rows.append(row3);

    m_normalsTop = m_normalsBottom;

    m_normalsBottom.clear();


    std::shared_ptr<QList<glm::vec3>> row2 = m_rows.at(2);
    generateNormal(row2, m_normalsBottom, 2);

}

glm::vec3 TriangleMeshCache::findNormal(glm::vec3 vertex, int col, int row){
    //std::cout << "col: " << col <<"  row: " << row << "  vertex: " << vertex << std::endl;
    assert(row == 1 || row == 2);
    QList<glm::vec3> normals;

    glm::vec3 vertexDown = getVertex(col, row +1);
    glm::vec3 vertexDownRight = getVertex(col+1, row +1);

    glm::vec3 vertexRight = getVertex(col+1, row);
    glm::vec3 vertexUpRight = getVertex(col+1, row-1);

    glm::vec3 vertexUp = getVertex(col, row -1);
    glm::vec3 vertexUpLeft = getVertex(col -1, row -1);

    glm::vec3 vertexLeft = getVertex(col -1, row);
    glm::vec3 vertexDownLeft = getVertex(col -1, row +1);

    normals.append(findTriangleNormal(vertex, vertexRight, vertexUpRight));
    normals.append(findTriangleNormal(vertex, vertexUpRight, vertexUp));
    normals.append(findTriangleNormal(vertex, vertexUp, vertexUpLeft));
    normals.append(findTriangleNormal(vertex, vertexUpLeft, vertexLeft));
    normals.append(findTriangleNormal(vertex, vertexLeft, vertexDownLeft));
    normals.append(findTriangleNormal(vertex, vertexDownLeft, vertexDown));
    normals.append(findTriangleNormal(vertex, vertexDown, vertexDownRight));
    normals.append(findTriangleNormal(vertex, vertexDownRight, vertexRight));


    glm::vec3 normalTotal = glm::vec3(0);
    for(glm::vec3 normal : normals){
        if(normal.y < 0){
            std::cout << "Warning: normal is pointing down: " << normal << std::endl;
        }
        normalTotal += normal;
    }

    return glm::normalize(normalTotal);
}

glm::vec3 TriangleMeshCache::findTriangleNormal(const glm::vec3 vertex1, const glm::vec3 vertex2, const glm::vec3 vertex3){
    return glm::normalize(glm::cross(vertex2-vertex1, vertex3-vertex1));
}

glm::vec3 TriangleMeshCache::getVertex(int col, int row){
    assert(row >= 0 || row < 4);
    std::shared_ptr<QList<glm::vec3>> rowVertex = m_rows.at(row);
    int index = col+1;
    assert(index >= 0 && index < rowVertex->size());
    return rowVertex->at(index);

}

glm::vec3 TriangleMeshCache::getNormal(int col, int row){
    assert(row == 1 || row == 2);
    if(row == 1){
        assert(col >= 0 && col < m_normalsTop.size());
        return m_normalsTop.at(col);
    }
    else{
        assert(col >= 0 && col < m_normalsBottom.size());
        return m_normalsBottom.at(col);
    }

}
