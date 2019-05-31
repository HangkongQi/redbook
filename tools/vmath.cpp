//
// Created by zac on 19-5-31.
//

#include "vmath.h"
#include <cstdlib>
#include <cstdio>
#include <cmath>

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

float *vmath::rotatef(float angle, float x, float y, float z)
{
    float *rom;
    rom = (float *)malloc(sizeof(float) * 16);

    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    float rads = float(angle) * 0.0174532925f;
    float c = cosf(rads);
    float s = sinf(rads);
    float omc = 1.0f - c;

    rom[0] = (x2 * omc + c);
    rom[1] = (y * x * omc + z * s);
    rom[2] = (x * z * omc - y * s);
    rom[3] = (0.0f);

    rom[4] = (x * y * omc - z * s);
    rom[5] = (y2 * omc + c);
    rom[6] = (y * z * omc + x * s);
    rom[7] = (0.0f);

    rom[8] = (x * z * omc + y * s);
    rom[9] = (y * z * omc - x * s);
    rom[10] = (z2 * omc + c);
    rom[11] = (0.0f);

    rom[12] = (0.0f);
    rom[13] = (0.0f);
    rom[14] = (0.0f);
    rom[15] = (1.0f);

    return rom;
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

float * vmath::orthof(float l, float r, float b, float t, float n, float f)
{
    float *orm;
    orm = (float *)malloc(sizeof(float) * 16);

    orm[0] = 2.0f/(r-l);
    orm[1] = 0.0f;
    orm[2] = 0.0f;
    orm[3] = - (r+l) / (r-l);

    orm[4] = 0.0f;
    orm[5] = 2.0f / (t-b);
    orm[6] = 0.0f;
    orm[7] = - (t+b) / (t-b);

    orm[8] = 0.0f;
    orm[9] = 0.0f;
    orm[10] = -2.0f / (f-n);
    orm[11] = - (f+n) / (f-n);

    orm[12] = 0.0f;
    orm[13] = 0.0f;
    orm[14] = 0.0f;
    orm[15] = 1.0f;

    return orm;
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