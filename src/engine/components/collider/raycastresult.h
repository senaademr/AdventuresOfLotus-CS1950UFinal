#ifndef RAYCASTRESULT_H
#define RAYCASTRESULT_H

class GameObject;
#include <memory>

struct RaycastResult
{
    RaycastResult(float t_value) :
        didCollide(true),
        t(t_value)
    {

    }
    RaycastResult()
        : didCollide(false),
          t(-1) {

    }

    bool didCollide;
    float t;
};

#endif // RAYCASTRESULT_H
