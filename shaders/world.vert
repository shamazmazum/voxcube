#version 450

layout(location = 0) in vec2 vertexIn;
layout(location = 1) in float zcoord;
layout(location = 0) out vec3 vertexOut;

uniform mat4 proj;
uniform mat4 world2cam;
uniform bvec3 invert_axes;

void main() {
    vec3 vertex = vec3 (vertexIn, zcoord);
    vec3 front = transpose (mat3 (world2cam)) * vec3 (0.0f, 0.0f, 1.0f);
    vec3 absfront = abs (front);
    float m = max (absfront.x, max (absfront.y, absfront.z));

    if (m == absfront.x) {
        vertex = vertex.zyx;
    } else if (m == absfront.y) {
        vertex = vertex.xzy;
    }

    gl_Position = proj * world2cam * vec4(vertex, 1.0f);
    vertexOut = mix (vertex, -vertex, invert_axes);
}
