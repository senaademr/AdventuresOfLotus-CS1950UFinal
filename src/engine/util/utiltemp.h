#ifndef UTIL_H
#define UTIL_H


#include <iostream>
#include "engine/components/componenttype.h"

class Util
{
public:
    static std::string componentTypeToString(ComponentType type);
};

#endif // UTIL_H
