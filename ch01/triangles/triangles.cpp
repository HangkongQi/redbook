//
// Created by qihangkong on 7/31/17.
//
#include <stdio.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include "LoadShaders.h"
#include "vgl.h"
#include "curr_config.h"

#include <iostream>
using namespace std;

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};

enum Attrib_IDs {vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

/*
 * init
 * */
void
init(void)
{
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    GLfloat vertices[NumVertices][2] = {
            {-0.90, -0.90},
            { 0.85, -0.90},
            {-0.90,  0.85},
            { 0.90, -0.85},
            { 0.90,  0.90},
            {-0.85,  0.90},
    };

    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, TOP_PATH "/ch01/triangles/triangle.vert"},
            {GL_FRAGMENT_SHADER, TOP_PATH "/ch01/triangles/triangle.frag"},
            {GL_NONE, NULL},
    };

    GLuint program = LoadShaders(shaders);

    glUseProgram(program);

    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
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
    glutInitWindowSize(480, 320);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("triangles");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 1;
}