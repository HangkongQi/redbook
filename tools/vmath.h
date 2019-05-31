//
// Created by zac on 19-5-31.
//

#ifndef REDBOOK_VMATH_H
#define REDBOOK_VMATH_H

#include <GL/glut.h>

namespace vmath {
    float * translation(float x, float y, float z);
    float * scale(float x, float y, float z);
    float * frustum(float l, float r, float b, float t, float n, float f);
    float * rotatef(float angle, float x, float y, float z);
    float * orthof(float l, float r, float b, float t, float n, float f);
};

#endif //REDBOOK_VMATH_H
