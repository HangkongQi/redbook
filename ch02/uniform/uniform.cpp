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

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, ColorBuffer, UniformBuffer, NumBuffers};

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

    GLfloat uniform_block_data[14][4] = {
            /* Model view */
            {0.5, 0.0, 0.0, 0.0},
            {0.0, 0.5, 0.0, 0.0},
            {0.0, 0.0, 0.5, 0.0},
            {0.0, 0.0, 0.0, 1.0},
            /* Projection */
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
            {GL_VERTEX_SHADER, TOP_PATH "/ch02/uniform/uniform.vert"},
            {GL_FRAGMENT_SHADER, TOP_PATH "/ch02/uniform/uniform.frag"},
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
    glBindBuffer(GL_UNIFORM_BUFFER, Buffers[UniformBuffer]);

    GLuint ub_index;
    ub_index = glGetUniformBlockIndex(program, "Matrices");
    printf("Uniform Block index is: %x\n", ub_index);

    GLint ub_size;
    glGetActiveUniformBlockiv(program, ub_index, GL_UNIFORM_BLOCK_DATA_SIZE, &ub_size);
    printf("Uniform Block Size is: 0x%x\n", ub_size);

    glBufferData(GL_UNIFORM_BUFFER, sizeof(uniform_block_data), uniform_block_data, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, ub_index, Buffers[UniformBuffer]);

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