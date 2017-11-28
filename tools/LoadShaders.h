//
// Created by qihangkong on 8/1/17.
//

#ifndef REDBOOK_LOADSHADERS_H
#define REDBOOK_LOADSHADERS_H

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

namespace Tools {

    typedef struct ShaderInfo {
        GLenum type;
        const char *filename;
        GLuint shader;
    } ShaderInfo;

    GLuint LoadShaders(ShaderInfo *shaders);

    static const GLchar* ReadShader( const char* filename );

    void GetVersionInfo(void);
}

#endif //REDBOOK_LOADSHADERS_H
