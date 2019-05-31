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
using namespace Tools;


const GLuint NumVertices = 4;

/*
 * init
 * */
void
init(void)
{
    GetVersionInfo();

    GLfloat position[] = {
            -1.0, -1.0, 0.0, 1.0,
             1.0, -1.0, 0.0, 1.0,
             1.0,  1.0, 0.0, 1.0,
            -1.0,  1.0, 0.0, 1.0,
    };

    GLfloat colors[] = {
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 1.0, 0.0,
    };

    /* Initialize shaders */
    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, TOP_PATH "/ch03/buffer_sub_data/buffer_sub_data.vert"},
            {GL_FRAGMENT_SHADER, TOP_PATH "/ch03/buffer_sub_data/buffer_sub_data.frag"},
            {GL_NONE, NULL},
    };

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);


    /* initialize buffer data */
    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(position), position);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(position), sizeof(colors), colors);

    /* Vertex Array */
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)sizeof(position));
    glEnableVertexAttribArray(1);
}

void reshape(int w, int h)
{
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_FAN, 0, NumVertices);

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("triangles");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 1;
}