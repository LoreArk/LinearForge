#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 fragPos;      // frag pos in world space
out vec3 fragNormal;   // normal in world space

void main() {
    vec4 worldPos = u_model * vec4(aPos, 1.0);
    fragPos    = vec3(worldPos);

    fragNormal = mat3(transpose(inverse(u_model))) * aNormal;

    gl_Position = u_projection * u_view * worldPos;
}