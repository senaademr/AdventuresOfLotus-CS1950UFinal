#ifndef DRAWABLE_H
#define DRAWABLE_H

class Graphics;

class Drawable
{
public:
    virtual void draw() = 0;

protected:
    Graphics* getGraphics();
};

#endif // DRAWABLE_H
