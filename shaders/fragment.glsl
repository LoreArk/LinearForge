#version 460 core

#define MAX_LIGHTS 8

struct Light {
    vec3  position;
    vec3  color;
    float intensity;
    int   type;
};

struct Material {
    vec3  color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
};

uniform Light    u_lights[MAX_LIGHTS];
uniform int      u_lightCount;
uniform Material u_mat;
uniform vec3     u_viewPos;

uniform bool u_wireframe;

in vec3 fragPos;
in vec3 fragNormal;

out vec4 FragColor;

void main() {

    if (u_wireframe) {
        FragColor = vec4(0.0, 1.0, 0.0, 1.0); // verde fisso
        return;
    }

    vec3 normal  = normalize(fragNormal);
    vec3 viewDir = normalize(u_viewPos - fragPos);

    // Ambient — deep dark shadows
    vec3 result = u_mat.ambient * u_mat.color;

    for (int i = 0; i < u_lightCount; i++) {
        Light l = u_lights[i];

        vec3 lightDir = normalize(l.position - fragPos);

        // Diffuse
        float diff    = max(dot(normal, lightDir), 0.0);
        vec3  diffuse = u_mat.diffuse * diff * l.color * l.intensity;

        // Specular 
        vec3  reflectDir = reflect(-lightDir, normal);
        float spec       = pow(max(dot(viewDir, reflectDir), 0.0), u_mat.shininess);
        vec3  specular   = u_mat.specular * spec * l.color * l.intensity;

        // Point light attenuation
        float dist = length(l.position - fragPos);
        float att  = 1.0 / (1.0 + 0.14 * dist + 0.07 * dist * dist);

        result += (diffuse + specular) * att * u_mat.color;
    }

    // ── Color grading ────────────────────────────────────────────
    // Contrast: flatens half tones, enhances blacks and whites
    result = (result - 0.5) * 1.4 + 0.5;

    // Subtle warm tint
    result *= vec3(1.05, 0.98, 0.92);

    // Final clamp
    result = clamp(result, 0.0, 1.0);
    // ─────────────────────────────────────────────────────────────

    FragColor = vec4(result, 1.0);
}