#include "rectangle.h"

Rectangle::Rectangle(int xMin, int xMax, int yMin, int yMax) :
    XMIN(xMin),
    XMAX(xMax),
    YMIN(yMin),
    YMAX(yMax)
{
    if(XMAX <= XMIN){
        std::cout << "xmin: " << XMIN << " must be less than xmax: " << XMAX << std::endl;
        throw -1;
    }
    if(YMAX <= YMIN){
        std::cout << "ymin: " << YMIN << " must be less than ymax: " << YMAX << std::endl;
        throw -1;
    }
}

int Rectangle::getWidth(){
    return XMAX-XMIN;
}
int Rectangle::getHeight(){
    return YMAX-YMIN;
}

bool Rectangle::inRectangle(glm::vec2 position){
    return position.x >= XMIN && position.x <= XMAX
            && position.y >= YMIN && position.y<= YMAX;
}


bool Rectangle::almostInRectangle(glm::vec2 position){
    return position.x + 1 >= XMIN && position.x -1<= XMAX
            && position.y +1>= YMIN && position.y -1<= YMAX;
}

std::string Rectangle::toString(){
    return "xMin: " + std::to_string(XMIN)
            + " xMax: " + std::to_string(XMAX)
            + " yMin: " + std::to_string(YMIN)
            + " yMax: " + std::to_string(YMAX);
}


QList<glm::ivec2> Rectangle::getPoints(){
    QList<glm::ivec2> points;
    for(int row = YMIN; row < YMAX; row ++){
        for(int col = XMIN; col < XMAX; col ++){
            points.append(glm::ivec2(col, row));
        }
    }
    return points;
}

glm::ivec2 Rectangle::getCenter(){
    //std::cout << "XMAX" <<XMAX << ",XMIN" << XMIN<< ",YMAX" << YMAX << ",YMIN" << YMIN  <<std::endl;
    //std::cout << "center: " << (XMAX-XMIN)/2 << ", " << (YMAX-YMIN)/2 << std::endl;
    return glm::ivec2((XMAX-XMIN)/2 + XMIN, (YMAX-YMIN)/2 + YMIN);
}
