#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include "LoadShaders.h"
#include "vgl.h"
#include "curr_config.h"

using namespace Tools;

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, ColorBuffer, NumBuffers};

enum Attrib_IDs {vPosition = 0, vColor = 1};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

size_t TypeSize(GLenum type)
{
    size_t size;
#define CASE(Enum, Count, Type) \
    case Enum: size = Count * sizeof(Type); break;

    switch (type) {
        CASE(GL_FLOAT, 1, GLfloat);
        CASE(GL_FLOAT_VEC2, 2, GLfloat);
        CASE(GL_FLOAT_VEC3, 3, GLfloat);
        CASE(GL_FLOAT_VEC4, 4, GLfloat);
        CASE(GL_INT, 1, GLint);
        CASE(GL_INT_VEC2, 2, GLint);
        CASE(GL_INT_VEC3, 3, GLint);
        CASE(GL_INT_VEC4, 4, GLint);
        CASE(GL_UNSIGNED_INT, 1, GLint);
        CASE(GL_UNSIGNED_INT_VEC2, 2, GLint);
        CASE(GL_UNSIGNED_INT_VEC3, 3, GLint);
        CASE(GL_UNSIGNED_INT_VEC4, 4, GLint);
        CASE(GL_BOOL, 1, GLboolean);
        CASE(GL_BOOL_VEC2, 2, GLboolean);
        CASE(GL_BOOL_VEC3, 3, GLboolean);
        CASE(GL_BOOL_VEC4, 4, GLboolean);
        CASE(GL_FLOAT_MAT2, 4, GLfloat);
        CASE(GL_FLOAT_MAT2x3, 6, GLfloat);
        CASE(GL_FLOAT_MAT2x4, 8, GLfloat);
        CASE(GL_FLOAT_MAT3, 9, GLfloat);
        CASE(GL_FLOAT_MAT3x2, 6, GLfloat);
        CASE(GL_FLOAT_MAT3x4, 12, GLfloat);
        CASE(GL_FLOAT_MAT4, 16, GLfloat);
        CASE(GL_FLOAT_MAT4x2, 8, GLfloat);
        CASE(GL_FLOAT_MAT4x3, 12, GLfloat);
#undef CASE
        default:
            printf("Unkonw TYpe: 0x%x\n", type);
            exit(EXIT_FAILURE);
    }

    return size;
}

void init()
{
    GLuint program;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, TOP_PATH "/ch02/uniform_block/uniform_block.vert"},
            {GL_FRAGMENT_SHADER, TOP_PATH "/ch02/uniform_block/uniform_block.frag"},
            {GL_NONE, NULL},
    };

    program = LoadShaders(shaders);
    glUseProgram(program);

    GLuint uboIndex;
    GLint  uboSize;
    GLuint ubo;
    GLchar *buffer;

    uboIndex = glGetUniformBlockIndex(program, "Uniforms");
    glGetActiveUniformBlockiv(program, uboIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);

    buffer = (GLchar *)malloc(uboSize);
    if (buffer == NULL) {
        printf("Unable to allocate buffer\n");
        exit(EXIT_FAILURE);
    } else {
        enum {Translation, Scale, Rotation, Enabled, NumUniforms};
        GLfloat scale = 0.5;
        GLfloat translation[] = {0.3, 0.2, 0.0};
        GLfloat rotation[] = {90.0, 1.0, 0.0, 1.0};
        GLboolean enabled = GL_TRUE;

        const char *names[NumUniforms] = {
                "translation",
                "scale",
                "rotation",
                "enabled",
        };

        GLuint indices[NumUniforms];
        GLint size[NumUniforms];
        GLint offset[NumUniforms];
        GLint type[NumUniforms];

        glGetUniformIndices(program, NumUniforms, names, indices);
        glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_OFFSET, offset);
        glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_SIZE, size);
        glGetActiveUniformsiv(program, NumUniforms, indices, GL_UNIFORM_TYPE, type);

        memcpy(buffer + offset[Scale], &scale, size[Scale] * TypeSize(type[Scale]));
        memcpy(buffer + offset[Translation], &translation, size[Translation] * TypeSize(type[Translation]));
        memcpy(buffer + offset[Rotation], &rotation, size[Rotation] * TypeSize(type[Rotation]));
        memcpy(buffer + offset[Enabled], &enabled, size[Enabled] * TypeSize(type[Rotation]));

        glGenBuffers(1, &ubo);
        glBindBuffer(GL_UNIFORM_BUFFER, ubo);
        glBufferData(GL_UNIFORM_BUFFER, uboSize, buffer, GL_STATIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, uboIndex, ubo);
    }

    GLfloat vertices[NumVertices][3] = {
            {-0.90, -0.90, 0.0},  // 1
            { 0.90, -0.90, 0.0},  // 2
            {-0.90,  0.90, 0.0},  // 3
            { 0.90, -0.90, 0.0},  // 2
            { 0.90,  0.90, 0.0},  // 4
            {-0.90,  0.90, 0.0},  // 3
    };
    GLfloat colors[NumVertices][4] = {
            {1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 1.0, 1.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
    };

    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

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
    glutCreateWindow("redbook");
    init();
    // glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 1;
}