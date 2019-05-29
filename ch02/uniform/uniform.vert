#version 430 core
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
out vec4 Color;

uniform Matrices {
    mat4 modelview;
    mat4 projection;
};

void
main()
{
    vec4 mp = modelview * vPosition;
    gl_Position = projection * mp;
    Color = vColor;
}