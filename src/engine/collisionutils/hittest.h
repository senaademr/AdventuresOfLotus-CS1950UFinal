#ifndef HITTEST_H
#define HITTEST_H
#include <glm/glm.hpp>
struct HitTest
{
    float t;
    glm::vec3 hit;
    glm::vec3 normal;

    HitTest() : t(INFINITY) {}
};
#endif // HITTEST_H
