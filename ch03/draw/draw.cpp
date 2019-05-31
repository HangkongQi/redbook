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

#define fpath "ch03/draw/draw"

GLuint render_model_matrix_loc;
GLuint render_projection_matrix_loc;
GLfloat aspect = 480.0/320.0;

/*
 * init
 * */
void
init(void)
{
    GetVersionInfo();

    GLfloat vertex_position[] = {
            -1.0f, -1.0f, 0.0f, 1.0f,
             1.0f, -1.0f, 0.0f, 1.0f,
            -1.0f,  1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 1.0f,
    };

    GLfloat vertex_colors[] = {
            1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 0.0, 1.0,
            1.0, 0.0, 1.0, 1.0,
            0.0, 1.0, 1.0, 1.0,
    };

    GLint vertex_indices[] = {
            0, 1, 2,
    };

    /* Initialize shaders */
    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, TOP_PATH fpath ".vert"},
            {GL_FRAGMENT_SHADER, TOP_PATH fpath ".frag"},
            {GL_NONE, NULL},
    };

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    render_model_matrix_loc = glGetUniformLocation(program, "modelview_matrix");
    render_projection_matrix_loc = glGetUniformLocation(program, "projection_matrix");

    /* indices array buffer*/
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

    /* Vertex Array buffer */
    GLuint vao;
    glGenBuffers(1, &vao);
    glBindBuffer(GL_ARRAY_BUFFER, vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_position) + sizeof(vertex_colors),
                 NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_position), vertex_position);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_position), sizeof(vertex_colors), vertex_colors);


    /* Vertex Array */
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)sizeof(vertex_position));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    aspect = (float)w / (float)h;
}

void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    float *proj = vmath::frustum(-1.0, 1.0, -aspect, aspect, 1.0f, 500.0f);
    glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, proj);

    float *model;
    /* glDrawArrays */
    model = vmath::translation(-3.0, 0.0, -5.0);
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* glDrawElements */
    model = vmath::translation(-1.0, 0.0, -5.0);
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);

    /* glDrawElementBaseVertex */
    model = vmath::translation(1.0, 0.0, -5.0);
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model);
    glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL, 1);

    /* glDrawArrayInstanced */
    model = vmath::translation(3.0, 0.0, -5.0);
    glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, model);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);
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