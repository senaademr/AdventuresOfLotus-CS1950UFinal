#ifndef RECTANGLE_H
#define RECTANGLE_H



#include "engine/util/CommonIncludes.h"
#include <QList>


class Rectangle
{
public:
    Rectangle(int xMin, int xMax, int yMin, int yMax);

    int getWidth();
    int getHeight();

    const int XMIN;
    const int XMAX;
    const int YMIN;
    const int YMAX;

    std::string toString();

    QList<glm::ivec2> getPoints();
    bool inRectangle(glm::vec2 position);
    bool almostInRectangle(glm::vec2 position);
    glm::ivec2 getCenter();

};

#endif // RECTANGLE_H
