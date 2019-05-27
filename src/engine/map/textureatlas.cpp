#include "textureatlas.h"

TextureAtlas::TextureAtlas(int texturesHorizontal, int texturesVertical)
    :     m_texturesHorizontal(texturesHorizontal),
        m_texturesVertical(texturesVertical)

{

}

void TextureAtlas::addTexture(std::string name, glm::ivec2 position){

    m_textureCoordinates.insert(name, position);
}

glm::vec2 TextureAtlas::toTextureCoords(std::string name, glm::vec2 baseCoords){
    if(!m_textureCoordinates.contains(name)){
        std::cout << "No texture with name: " << name << std::endl;
        throw -1;
    }
    glm::ivec2 textureCoord = m_textureCoordinates.value(name);
    float x = static_cast<float>(textureCoord.x) + baseCoords.x;
    float y = static_cast<float>(textureCoord.y)+baseCoords.y;
    return glm::vec2(x/m_texturesHorizontal, y/m_texturesVertical);
}


bool TextureAtlas::hasTexture(std::string name){
    return m_textureCoordinates.contains(name);
}
