#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include "engine/util/CommonIncludes.h"
#include <QMap>



class TextureAtlas
{
public:
    TextureAtlas(int texturesHorizontal, int texturesVertical);
    void addTexture(std::string name, glm::ivec2 position);
    glm::vec2 toTextureCoords(std::string name, glm::vec2 baseCoords);
    bool hasTexture(std::string name);

private:
    QMap<std::string, glm::ivec2> m_textureCoordinates;

    float m_texturesHorizontal;
    float m_texturesVertical;
};

#endif // TEXTUREATLAS_H
