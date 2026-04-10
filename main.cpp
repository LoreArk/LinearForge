#include "include/Engine.hpp"
#include "SceneLoader.hpp"
#include "MeshLibrary.hpp"
#include "Mesh.hpp"
#include "PrimitiveMeshes.hpp"
#include <iostream>

int main() {
    Engine forge;
    if (!forge.init(1280, 720, "Linear Forge Engine"))
        return -1;

    // Register available meshes
    MeshLibrary meshLib;
    meshLib.add("cube",    PrimitiveMeshes::cube());
    meshLib.add("plane",   PrimitiveMeshes::plane());
    meshLib.add("pyramid", PrimitiveMeshes::pyramid());

    // Load scene from file
    Scene* scene = forge.createScene();
    scene->camera = Camera(
        glm::vec3(0.0f, 0.0f, 4.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        45.0f, 1280.0f / 720.0f
    );

    SceneLoader::load("../scenes/main.json", *scene, meshLib);

    glfwSetInputMode(forge.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    while (forge.isRunning()) {
        forge.update();
        forge.render();
    }

    forge.terminate();
    return 0;
}