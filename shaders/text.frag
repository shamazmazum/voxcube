#version 450

layout(location = 0) in vec2 uv;
layout(location = 0) out vec4 outColor;

uniform sampler2D sampler;

void main () {
    outColor = texture (sampler, uv);
}
