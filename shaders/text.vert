#version 450

layout(location = 0) in vec2 vertexPos;
layout(location = 1) in vec2 vertexUV;
layout(location = 0) out vec2 uv;

void main ()
{
    gl_Position = vec4 (vertexPos, 0.0, 1.0);
    uv = vertexUV;
}
