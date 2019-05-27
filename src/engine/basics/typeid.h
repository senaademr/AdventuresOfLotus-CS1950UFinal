#ifndef TYPEID_H
#define TYPEID_H


#include <memory>

class TypeID
{
    static size_t counter;

public:
    template<typename T>
    static size_t value()
    {
        static size_t id = counter++;
        return id;
    }
};


#endif // TYPEID_H
