#ifndef UIELEMENT_H
#define UIELEMENT_H

#include "engine/util/CommonIncludes.h"

class Graphics;

enum UIType{NONE=0, TEXT=1, SHAPE=2, BUTTON=3, SLIDER=4};

class UIElement
{
public:
    UIElement();
    virtual ~UIElement();
    virtual void draw();
    virtual void tick(float seconds);

    void setRelativePosition(glm::vec3 pos);
    void setRelativeDimensions(glm::vec2 dim);

    void setOrthographic(bool ortho);
    bool getOrthographic();

    void setInteractive(bool interactive);
    bool getInteractive();

    virtual void callback();

    UIType getType();

protected:
    Graphics* m_graphics;
    bool isOrthographic = false;
    bool isInteractive = false;
    UIType m_type;
    glm::vec3 m_relativePos = glm::vec3(0.f);
    glm::vec2 m_relativeDimensions = glm::vec2(0.f);
};

#endif // UIELEMENT_H
