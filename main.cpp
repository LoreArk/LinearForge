#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "include/Engine.hpp"
#include "TransformComponent.h"
#include "RenderComponent.hpp"
#include "MaterialComponent.hpp"  
#include "LightComponent.hpp"    
#include "Mesh.hpp"
#include <iostream>

int main() {
    Engine forge;
    if (!forge.init(1280, 720, "Linear Forge Engine"))
        return -1;

    Scene* scene = forge.createScene();
    scene->camera = Camera(
        glm::vec3(0.0f, 0.0f, 4.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        45.0f,
        1280.0f / 720.0f
    );

    Entity* player = scene->addEntity();
    player->addComponent<InputComponent>();

    glfwSetInputMode(forge.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // ── Mesh ─────────────────────────────────────────────
    auto cubeMesh = std::make_shared<Mesh>(
        std::vector<float>{
        //  x      y      z      nx     ny     nz
            // Davanti
           -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
           -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            // Dietro
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            // Sinistra
           -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            // Destra
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            // Sopra
           -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            // Sotto
           -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        },
        std::vector<unsigned int>{
             0, 1, 2,  2, 3, 0,
             4, 5, 6,  6, 7, 4,
             8, 9,10, 10,11, 8,
            12,13,14, 14,15,12,
            16,17,18, 18,19,16,
            20,21,22, 22,23,20,
        },
        6
    );

    // ── Cube ──────────────────────────────────────────────────────
    Entity* cube = scene->addEntity();
    auto* transform = cube->addComponent<TransformComponent>();
    cube->addComponent<RenderComponent>(cubeMesh);
    auto* mat = cube->addComponent<MaterialComponent>();
    mat->color = glm::vec3(0.7f, 0.45f, 0.3f);
    transform->spinSpeed = glm::vec3(0.0f, 30.0f, 10.0f);

    Entity* cube2 = scene->addEntity();
    auto* transform2 = cube2->addComponent<TransformComponent>();
    cube2->addComponent<RenderComponent>(cubeMesh);
    auto* mat2 = cube2->addComponent<MaterialComponent>();
    mat2->color = glm::vec3(0.0f, 0.45f, 0.0f);
    transform2->position = glm::vec3(5.f, 0.f, 0.f);
    transform2->spinSpeed = glm::vec3(0.0f, 30.0f, 10.0f);

    // ── Lights ──────────────────────────────────────────────────────
    Entity* sun = scene->addEntity();
    auto* sunLight = sun->addComponent<LightComponent>();
    sunLight->color     = glm::vec3(1.0f, 0.92f, 0.75f);
    sunLight->intensity = 3.0f;
    sun->addComponent<TransformComponent>()->position = glm::vec3(3.0f, 4.0f, 2.0f);

    Entity* fill = scene->addEntity();
    auto* fillLight = fill->addComponent<LightComponent>();
    fillLight->color     = glm::vec3(0.4f, 0.5f, 0.8f);
    fillLight->intensity = 3.f;
    fill->addComponent<TransformComponent>()->position = glm::vec3(-2.0f, -1.0f, 1.0f);

    // ── Loop ──────────────────────────────────────────────────────
    while (forge.isRunning()) {
        forge.update();
        forge.render();
    }

    forge.terminate();
    return 0;
}