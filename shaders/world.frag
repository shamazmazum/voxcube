#version 450

layout(location = 0) in vec3 vertexIn;
layout(location = 0) out vec4 color;

uniform sampler3D sampler;

void main() {
    vec3 coord = 0.5f + 0.5f*vertexIn;
    float density = texture (sampler, coord).r;
    density = (density > 0.2f)? density/8: 0.0f;
    color = vec4 (0.0f, 1.0f, 0.0f, density);
}
