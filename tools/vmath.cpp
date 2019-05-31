//
// Created by zac on 19-5-31.
//

#include "vmath.h"
#include <cstdlib>
#include <cstdio>

float* vmath::translation(float x, float y, float z)
{
    float *trans;
    trans = (float *)malloc(sizeof(float) * 16);
    if (trans == NULL) {
        printf("Error to malloc\n");
        return NULL;
    }

    trans[0] = 1.0f;
    trans[1] = 0.0f;
    trans[2] = 0.0f;
    trans[3] = 0.0f;

    trans[4] = 0.0f;
    trans[5] = 1.0f;
    trans[6] = 0.0f;
    trans[7] = 0.0f;

    trans[8] = 0.0f;
    trans[9] = 0.0f;
    trans[10] = 1.0f;
    trans[11] = 0.0f;

    trans[12] = x;
    trans[13] = y;
    trans[14] = z;
    trans[15] = 1.0f;

    return trans;
}

float* vmath::scale(float x, float y, float z)
{
    float *scal;
    scal = (float *)malloc(sizeof(float)*16);

    scal[0] = x;
    scal[1] = 0.0f;
    scal[2] = 0.0f;
    scal[3] = 0.0f;

    scal[4] = 0.0f;
    scal[5] = y;
    scal[6] = 0.0f;
    scal[7] = 0.0f;

    scal[8] = 0.0f;
    scal[9] = 0.0f;
    scal[10] = z;
    scal[11] = 0.0f;

    scal[12] = 0.0f;
    scal[13] = 0.0f;
    scal[14] = 0.0f;
    scal[15] = 1.0f;

    return scal;
}

float * vmath::frustum(float l, float r, float b, float t, float n, float f)
{
    float *proj;
    proj = (float *)malloc(sizeof(float) * 16);

    proj[0] = (2.0 * n)/(r - l);
    proj[1] = 0;
    proj[2] = (r + l) / (r - l);
    proj[3] = 0;

    proj[4] = 0;
    proj[5] = (2.0 * n) / (t - b);
    proj[6] = (t + b) / (t - b);
    proj[7] = 0;

    proj[8] = 0;
    proj[9] = 0;
    proj[10] = -(f + n) / (f - n);
    proj[11] = -(2.0 * f * n) / (f - n);

    proj[12] = 0;
    proj[13] = 0;
    proj[14] = -1;
    proj[15] = 0;

    return proj;
}