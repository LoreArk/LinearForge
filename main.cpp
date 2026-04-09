#include <glad/glad.h>  // MUST be first: manages OpenGL function pointers
#include <GLFW/glfw3.h> // Manages window and input
#include <glm/glm.hpp>  // Core GLM math (vec3, mat4)
#include <glm/gtc/matrix_transform.hpp> // Matrix transformations (translate, scale, ortho)
#include <glm/gtc/type_ptr.hpp>        // Conversion from GLM matrices to raw float arrays for GPU
#include "include/Engine.hpp"
#include "TransformComponent.h"
#include "RenderComponent.hpp"
#include "Mesh.hpp"
#include <iostream>

int main() {
    Engine forge;
    std::cout << "A. engine created" << std::endl;
    
    if (!forge.init(1280, 720, "Linear Forge Engine"))
        return -1;
    std::cout << "B. init done" << std::endl;

    Scene* scene = forge.createScene();
    std::cout << "C. scene created" << std::endl;

    scene->camera = Camera(
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        45.0f,
        1280.0f / 720.0f
    );

    std::cout << "D. camera set" << std::endl;

    auto mesh = std::make_shared<Mesh>(
            std::vector<float>{
            //  x      y      z      nx     ny     nz
                // Davanti (normale 0,0,1)
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                // Dietro (normale 0,0,-1)
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                // Sinistra (normale -1,0,0)
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                // Destra (normale 1,0,0)
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                // Sopra (normale 0,1,0)
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                // Sotto (normale 0,-1,0)
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            },
            std::vector<unsigned int>{
                0, 1, 2,  2, 3, 0,   // davanti
                4, 5, 6,  6, 7, 4,   // dietro
                8, 9,10, 10,11, 8,   // sinistra
                12,13,14, 14,15,12,   // destra
                16,17,18, 18,19,16,   // sopra
                20,21,22, 22,23,20,   // sotto
            },
            6  // stride: 3 pos + 3 normal
        );
    
    std::cout << "E. mesh created" << std::endl;

    Entity* cube = scene->addEntity();
    
    cube->addComponent<TransformComponent>();
    cube->addComponent<RenderComponent>(mesh);

    auto* transform = cube->getComponent<TransformComponent>();
    transform->position = glm::vec3(1.0f, 0.0f, 0.0f);
    transform->scale    = glm::vec3(1.0f);
    transform->spinSpeed = glm::vec3(20.0f, 90.0f, 0.0f);

    std::cout << "F. entity created" << std::endl;
    // dopo forge.init() e prima del loop
    forge.mainShader->use();
    forge.mainShader->setVec3("u_lightPos",    glm::vec3(2.0f, 3.0f, 2.0f));
    forge.mainShader->setVec3("u_lightColor",  glm::vec3(1.0f, 1.0f, 1.0f));
    forge.mainShader->setVec3("u_objectColor", glm::vec3(0.4f, 0.6f, 0.9f));
    forge.mainShader->setVec3("u_viewPos",     glm::vec3(0.0f, 0.0f, 3.0f));
    std::cout << "G. entering loop" << std::endl;
    while (forge.isRunning()) {
        forge.update();
        forge.render();
    }

    forge.terminate();
    return 0;
}
