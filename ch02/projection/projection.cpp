//
// Created by qihangkong on 7/31/17.
//
#include <stdio.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include "LoadShaders.h"
#include "vgl.h"
#include "curr_config.h"
#include "vmath.h"

#include <iostream>
using namespace std;
using namespace Tools;

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, ColorBuffer, NumBuffers};

enum Attrib_IDs {vPosition = 0, vColor = 1};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

/*
 * init
 * */
void
init(void)
{
    GetVersionInfo();

    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    GLfloat vertices[NumVertices][3] = {
            {-0.90, -0.90, 0.0},  // 1
            { 0.90, -0.90, 0.0},  // 2
            {-0.90,  0.90, -1.0},  // 3
            { 0.90, -0.90, 0.0},  // 2
            { 0.90,  0.90, -1.0},  // 4
            {-0.90,  0.90, -1.0},  // 3
    };

    GLfloat colors[NumVertices][4] = {
            {1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 1.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
    };
    GLfloat modelview_matrix[4][4] = {
            {0.5, 0.0, 0.0, 0.0},
            {0.0, 0.5, 0.0, 0.0},
            {0.0, 0.0, 0.5, 0.0},
            {0.0, 0.0, 0.0, 1.0},
    };
    GLfloat projection_matrix[4][4] = {
#if 0
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, -1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0},
#else
            {1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, -3.0, -4.0},
            {0.0, 0.0, -1.0, 0.0},
#endif
    };


    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, TOP_PATH "/ch02/projection/projection.vert"},
            {GL_FRAGMENT_SHADER, TOP_PATH "/ch02/projection/projection.frag"},
            {GL_NONE, NULL},
    };
    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    glGenBuffers(NumBuffers, Buffers);
    /* Position Buffer */
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);

    /* Color Buffer */
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ColorBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vColor);

    /* Modelview Matrix With uniform */
    GLint mLoc;
    mLoc = glGetUniformLocation(program, "modelview");
    // GLfloat *model = vmath::scale(0.5, 0.5, 1.0);
    GLfloat *model = vmath::translation(0.3, 0, 0);
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, (GLfloat *)model);

    GLint pLoc;
    pLoc = glGetUniformLocation(program, "projection");
    GLfloat * proj = vmath::frustum(-2, 2, -2, 2, 1, 500);
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, (GLfloat *)proj);
}

void reshape(int w, int h)
{
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("redbooks");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 1;
}