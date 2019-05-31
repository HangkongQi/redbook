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

#define fpath "ch03/primitive_restart/primitive_restart"

GLuint render_translate_matrix_loc;
GLuint render_rotate_matrix_loc;
GLuint render_projection_matrix_loc;
GLfloat aspect = 480.0/320.0;

GLfloat rotate = 0.0f;

/*
 * init
 * */
void
init(void)
{
    GetVersionInfo();

    GLfloat cube_position[] = {
            -1.0f, -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f,  1.0f, 1.0f,
            -1.0f,  1.0f, -1.0f, 1.0f,
            -1.0f,  1.0f,  1.0f, 1.0f,
             1.0f, -1.0f, -1.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 1.0f,
             1.0f,  1.0f, -1.0f, 1.0f,
             1.0f,  1.0f,  1.0f, 1.0f,
    };

    GLfloat cube_colors[] = {
            1.0f, 1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.5f,
    };

    GLuint cube_indices[] = {
            0, 1, 2, 3, 6, 7, 4, 5, 0, 1,
            0xffff,
            1, 5, 3, 7,
            0xffff,
            0, 4, 2, 6,
    };

    /* Initialize shaders */
    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, TOP_PATH fpath ".vert"},
            {GL_FRAGMENT_SHADER, TOP_PATH fpath ".frag"},
            {GL_NONE, NULL},
    };

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    render_translate_matrix_loc = glGetUniformLocation(program, "translate_matrix");
    render_rotate_matrix_loc = glGetUniformLocation(program, "rotate_matrix");
    render_projection_matrix_loc = glGetUniformLocation(program, "projection_matrix");
    printf("%x\n", render_translate_matrix_loc);
    printf("%x\n", render_rotate_matrix_loc);
    printf("%x\n", render_projection_matrix_loc);

    /* indices array buffer*/
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    /* Vertex Array buffer */
    GLuint vao;
    glGenBuffers(1, &vao);
    glBindBuffer(GL_ARRAY_BUFFER, vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_position) + sizeof(cube_colors),
                 NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cube_position), cube_position);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(cube_position), sizeof(cube_colors), cube_colors);


    /* Vertex Array */
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)sizeof(cube_position));
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
    while (1) {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        float *proj = vmath::frustum(-3.0, 3.0, -3, 3, 1.0f, 5.0f);
        // float *proj = vmath::orthof(-3, 3, -3, 3, -3, 3);
        glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, proj);

        float *trans;
        float *rot;
        /* glDrawArrays */
        trans = vmath::translation(0, 0, -2);
        glUniformMatrix4fv(render_translate_matrix_loc, 1, GL_FALSE, trans);

        rot = vmath::rotatef(rotate, 1, 0, 0);
        glUniformMatrix4fv(render_rotate_matrix_loc, 1, GL_FALSE, rot);

        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(0xffff);
        glDrawElements(GL_TRIANGLE_STRIP, 20, GL_UNSIGNED_INT, NULL);

        rotate += 0.1;
        if (rotate >= 360.0) {
            rotate = 0;
        }

        glFlush();
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("triangles");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 1;
}