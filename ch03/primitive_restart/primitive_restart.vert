#version 430 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
out vec4 vcolor;

uniform mat4 translate_matrix;
uniform mat4 rotate_matrix;
uniform mat4 projection_matrix;

void
main(void)
{
    vec4 v0 = rotate_matrix * vPosition;
    vec4 v1 = translate_matrix * v0;
    gl_Position = projection_matrix * v1;
    vcolor =vColor;
}