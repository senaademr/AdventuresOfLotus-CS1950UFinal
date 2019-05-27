#ifndef AABBOX_H
#define AABBOX_H
/**
 * Adopted from:
 * https://www.scratchapixel.com/code.php?id=10&origin=/lessons/3d-basic-rendering/&src=1
 * */
#include "glm/glm.hpp"
struct Ray;
class AABBox
{
public:
    AABBox(const glm::vec3 &b0, const glm::vec3 &b1);
    ~AABBox();
    bool intersect(const Ray &r, float &t) const;
private:
    glm::vec3 m_bounds[2];
};

#endif // AABBOX_H
