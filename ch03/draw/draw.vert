#version 430 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
out vec4 vcolor;

uniform mat4 modelview_matrix;
uniform mat4 projection_matrix;

void
main(void)
{
    gl_Position = projection_matrix * (modelview_matrix * vPosition);
    vcolor =vColor;
}