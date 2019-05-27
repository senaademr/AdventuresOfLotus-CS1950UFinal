#ifndef CULLMATH_H
#define CULLMATH_H

#include "engine/util/CommonIncludes.h"
#include <QList>

class CullMath
{
public:
    static bool shouldCullCorners(QList<glm::vec4> &planes, QList<glm::vec4> corners);
    static bool cullPlane(glm::vec4 &plane, QList<glm::vec4> &corners);
};

#endif // CULLMATH_H
