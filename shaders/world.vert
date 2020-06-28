#version 450

layout(location = 0) in vec3 vertexIn;
layout(location = 1) in float zcoord;
layout(location = 0) out vec3 vertexOut;

uniform mat4 proj;
uniform mat4 world2cam;

void main() {
    vec3 vcoord = vertexIn + vec3 (0.0f, 0.0f, zcoord);
    //vcoord = vcoord.xzy;
    gl_Position = proj * world2cam * vec4(vcoord, 1.0f);
    vertexOut = vcoord;
}
