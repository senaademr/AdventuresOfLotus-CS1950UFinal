#ifndef POINT_H
#define POINT_H

#include <QString>
#include <QSet>
#include <glm/glm.hpp>


struct Point{
    Point(int x, int y)
        : x(x), y(y){

    }
    Point(const Point &p)
        :x(p.x), y(p.y){
    }
    Point(glm::ivec2 vec)
        :x(vec.x), y(vec.y)
    {

    }

    Point() :x(-100), y(-100){

    }

    int x;
    int y;

    Point operator +(const Point& other){
      return Point(this->x + other.x, this->y + other.y);
    }
    Point operator -(const Point& other){
      return Point(this->x - other.x, this->y - other.y);
    }
};

inline uint qHash(const Point &v){
    return qHash(QString::number(v.x) + QString::number(v.y));
}

inline bool operator==(const Point v1, const Point &v2)
{
    return (v1.x == v2.x && v1.y == v2.y);
}


inline bool operator!=(const Point &v1, const Point &v2){
    return !(v1 == v2);
}


#endif // POINT_H
