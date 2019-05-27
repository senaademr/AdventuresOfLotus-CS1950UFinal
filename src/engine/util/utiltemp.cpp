#include "util.h"




std::string Util::componentTypeToString(ComponentType type){
    switch(type){
    case ComponentType::DRAW:
        return "DRAW";
    case ComponentType::POSITION:
        return "POSITION";
    case ComponentType::PLAYER_INPUT:
        return "PLAYER_INPUT";
    case ComponentType::PHYSICS:
        return "PHYSICS";
    case ComponentType::COLLISION:
        return "COLLISION";
    case ComponentType::CAMERA :
        return "CAMERA";
    }
}
