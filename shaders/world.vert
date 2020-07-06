#version 450

layout(location = 0) in vec2 vertexIn;
layout(location = 0) out vec3 vertexOut;

uniform mat4 proj;
uniform mat4 world2cam;
uniform bvec3 invert_axes;
uniform uint nplanes;

void main() {
    vec3 vertex;
    float z = 2.0f * gl_InstanceID / (nplanes - 1) - 1.0f;
    vec3 front = transpose (mat3 (world2cam)) * vec3 (0.0f, 0.0f, 1.0f);
    vec3 absfront = abs (front);
    float m = max (absfront.x, max (absfront.y, absfront.z));

    if (m == absfront.x) {
        vertex = vec3 (z * sign (front.x), vertexIn.yx);
    } else if (m == absfront.y) {
        vertex = vec3 (vertexIn.x, z * sign (front.y), vertexIn.y);
    } else {
        vertex = vec3 (vertexIn, z * sign (front.z));
    }

    gl_Position = proj * world2cam * vec4(vertex, 1.0f);
    vertexOut = mix (vertex, -vertex, invert_axes);
}
