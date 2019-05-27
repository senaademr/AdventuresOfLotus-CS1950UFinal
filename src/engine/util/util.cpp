#include "util.h"

#include <assert.h>
#include <glm/gtx/string_cast.hpp>
#include <string>

//std::string Util::componentTypeToString(ComponentType type){
//    switch(type){
//    case ComponentType::DRAW:
//        return "DRAW";
//    case ComponentType::POSITION:
//        return "POSITION";
//    case ComponentType::PLAYER_INPUT:
//        return "PLAYER_INPUT";
//    case ComponentType::PHYSICS:
//        return "PHYSICS";
//    case ComponentType::COLLISION:
//        return "COLLISION";
//    case ComponentType::CAMERA :
//        return "CAMERA";
//    default:
//        return "Unlabeled componentType";
//    }
//    assert(false);
//    return "";
//}

QList<Direction> Util::getDirections(){
    QList<Direction> directions;
    directions.append(Direction::LEFT);
    directions.append(Direction::UP);
    directions.append(Direction::RIGHT);
    directions.append(Direction::DOWN);
    return directions;
}

QMap<Direction, glm::ivec2> Util::getDirectionOffsets(){
    QMap<Direction, glm::ivec2> offsets;
    offsets.insert(Direction::LEFT, glm::ivec2(-1, 0));
    offsets.insert(Direction::UP, glm::ivec2(0, -1));
    offsets.insert(Direction::RIGHT, glm::ivec2(1, 0));
    offsets.insert(Direction::DOWN, glm::ivec2(0, 1));
    return offsets;
}



std::string Util::directionToString(Direction dir){
    switch(dir){
        case(Direction::UP):
            return "UP";
        case(Direction::LEFT):
            return "LEFT";
        case(Direction::DOWN):
            return "DOWN";
        case(Direction::RIGHT):
            return "RIGHT";
    }
    //should never get here;
    assert(false);
    return "";

}

Direction Util::getReverseDirection(Direction dir){
    switch(dir){
        case(Direction::UP):
            return Direction::DOWN;
        case(Direction::LEFT):
            return Direction::RIGHT;
        case(Direction::DOWN):
            return Direction::UP;
        case(Direction::RIGHT):
            return Direction::LEFT;
    }
    //should never get here;
    assert(false);
    return Direction::UP;
}

//std::string Util::cellToString(Cell cell){
//    return "Cell: " + cellTypeToString(cell.type) + " number: " + std::to_string(cell.number);
//}

//std::string Util::cellTypeToString(CellType type){
//    switch(type){
//        case(CellType::EMPTY):
//        return "EMPTY";
//    case(CellType::HALLWAY):
//        return "HALLWAY";
//    case(CellType::ROOM):
//        return "ROOM";
//    }
//    //should never get here;
//    assert(false);
//    return "";
//}

//std::string Util::rayToString(Ray &ray){
//    return "Ray: origin " + glm::to_string(ray.getOrigin()) + " look: "
//            + glm::to_string(ray.getDirection()) + " inverseLook: " + glm::to_string(ray.getInverseDirection());
//}

std::string Util::pointToString(Point p){
    return "Point: (" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
}

std::string Util::fontMetricsToString(FontMetrics &f){
    return "Font metrics(ascent: " + std::to_string(f.ascent)
            + ", descent: " + std::to_string(f.descent)
            + ", width: " + std::to_string(f.width) + ")";
}
