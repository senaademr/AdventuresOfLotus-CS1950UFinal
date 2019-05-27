#ifndef RAY_H
#define RAY_H
/**
 * Adopted from:
 * https://www.scratchapixel.com/code.php?id=10&origin=/lessons/3d-basic-rendering/&src=1
 * */
#include "glm/glm.hpp"
struct Ray
{
    Ray(const glm::vec3 &orig, const glm::vec3 &dir) : orig(orig), dir(dir)
    {
        invdir = 1.f / dir;
        sign[0] = (invdir.x < 0);
        sign[1] = (invdir.y < 0);
        sign[2] = (invdir.z < 0);
    }
    glm::vec3 orig, dir; // ray orig and dir
    glm::vec3 invdir;
    int sign[3];
};
#endif // RAY_H
