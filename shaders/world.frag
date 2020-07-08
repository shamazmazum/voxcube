#version 450

layout(location = 0) in vec3 vertexIn;
layout(location = 0) out vec4 color;

uniform sampler3D sampler;
uniform samplerBuffer colormap;
uniform float threshold;
uniform int colors;

void main() {
    vec3 coord = 0.5f + 0.5f*vertexIn;
    float density = texture (sampler, coord).r;
    int i;

    if (density < threshold) {
        discard;
    }

    color = vec4 (0.0f, 1.0f, 0.0f, density / 16.0f);
    for (i=0; i<colors; i++) {
        vec4 mapcolor = texelFetch (colormap, i);
        if (density < mapcolor.a) {
            color = vec4 (mapcolor.rgb, density / 16.0f);
            break;
        }
    }
}
