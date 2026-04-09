#version 460 core

in vec3 fragPos;
in vec3 fragNormal;

uniform vec3 u_lightPos;      // posizione della luce nel world space
uniform vec3 u_viewPos;       // posizione della camera (per specular)
uniform vec3 u_objectColor;   // colore dell'oggetto
uniform vec3 u_lightColor;    // colore della luce

out vec4 FragColor;

void main() {
    vec3 normal   = normalize(fragNormal);
    vec3 lightDir = normalize(u_lightPos - fragPos);
    vec3 viewDir  = normalize(u_viewPos  - fragPos);

    // Ambient — luce base sempre presente
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * u_lightColor;

    // Diffuse — dipende dall'angolo luce/normale (dot product)
    // max(0) evita valori negativi quando la luce è dietro la faccia
    float diff    = max(dot(normal, lightDir), 0.0);
    vec3 diffuse  = diff * u_lightColor;

    // Specular — riflesso, dipende dall'angolo vista/riflesso
    float specularStrength = 0.5;
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular   = specularStrength * spec * u_lightColor;

    vec3 result = (ambient + diffuse + specular) * u_objectColor;
    FragColor   = vec4(result, 1.0);
}