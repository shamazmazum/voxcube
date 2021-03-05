#version 450

layout(location = 0) in vec2 uv;
layout(location = 0) out vec4 outColor;

uniform sampler2D sampler;

void main () {
    float tr = texture (sampler, uv).r;
    outColor = vec4 (vec3 (1.0), tr != 0);
}
