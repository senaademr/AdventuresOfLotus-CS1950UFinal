#include "drawable.h"

#include "engine/graphics/Graphics.h"


Graphics* Drawable::getGraphics(){
    return Graphics::getGlobalInstance();
}
