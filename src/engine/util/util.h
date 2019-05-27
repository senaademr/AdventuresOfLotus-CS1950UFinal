#ifndef UTIL_H
#define UTIL_H

#include <iostream>

#include <QMap>

#include "engine/components/componenttype.h"
#include "engine/map/direction.h"
#include "dungeon_crawler/map/point.h"
#include "engine/util/CommonIncludes.h"
#include "engine/graphics/Font.h"


class Ray;

class Util
{
public:
    static QList<Direction> getDirections();
    static QMap<Direction, glm::ivec2> getDirectionOffsets();
    static Direction getReverseDirection(Direction dir);

    //static std::string componentTypeToString(ComponentType type);
    static std::string directionToString(Direction dir);
    static std::string rayToString(Ray &ray) ;
//    static std::string cellToString(Cell cell);
//    static std::string cellTypeToString(CellType type);
    static std::string pointToString(Point p);
    static std::string fontMetricsToString(FontMetrics &f);

};



//inline std::ostream& operator<< (std::ostream& stream,const ComponentType& type) {
//    return stream << Util::componentTypeToString(type);
//}

inline std::ostream& operator<< (std::ostream& stream,const Point& point) {
    return stream << Util::pointToString(point);
}

inline std::ostream& operator<< (std::ostream& stream,const Direction& dir) {
    return stream << Util::directionToString(dir);
}
//inline std::ostream& operator<< (std::ostream& stream,const Ray& ray) {
//    return stream << Util::rayToString(ray);
//}
//inline std::ostream& operator<< (std::ostream& stream,const Cell& point) {
//    return stream << Util::cellToString(point);
//}
//inline std::ostream& operator<< (std::ostream& stream,const CellType& celltype) {
//    return stream << Util::cellTypeToString(celltype);
//}

inline std::ostream& operator<<(std::ostream& out, const glm::vec3& g)
{
    return out << glm::to_string(g);
}

inline std::ostream& operator<<(std::ostream& out, const glm::vec2& g)
{
    return out << glm::to_string(g);
}
inline std::ostream& operator<<(std::ostream& out, const glm::ivec2& g)
{
    return out << glm::to_string(g);
}

#endif // UTIL_H
