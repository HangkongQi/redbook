#version 430 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
out vec4 Color;

uniform mat4 modelview;

void
main()
{
    gl_Position = modelview * vPosition;
    Color = vColor;
}