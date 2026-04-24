#include "Engine.hpp"
#include <filesystem>
#include <iostream>

Engine::Engine() : window(nullptr), mainShader(nullptr) {}

bool Engine::init(int width, int height, const char* title) {
    std::cout << "1. init glfw" << std::endl;
    if (!glfwInit()) return false;
    
    std::cout << "2. create window" << std::endl;
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) return false;
    
    std::cout << "3. make context current" << std::endl;
    glfwMakeContextCurrent(window);
    
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods) {
        Engine* engine = static_cast<Engine*>(glfwGetWindowUserPointer(w));
        if (action == GLFW_PRESS) {
            if (key == GLFW_KEY_F)
                engine->toggleWireframe();
            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(w, true);
        }
    });

    std::cout << "4. load glad" << std::endl;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return false;
    
    std::cout << "5. create shader" << std::endl;
    mainShader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    
    glEnable(GL_DEPTH_TEST);

    std::cout << "6. init done, shader ID: " << mainShader->ID << std::endl;
    return true;
}

void Engine::update() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glfwPollEvents();
    
    if (currentScene)
        currentScene->update(deltaTime, window);
}

void Engine::render() {
    // Cleaning
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (currentScene)
    {
        mainShader->use();
        currentScene->render(mainShader);
    }
        
    glfwSwapBuffers(window);
}

bool Engine::isRunning() {
    return !glfwWindowShouldClose(window);
}

void Engine::terminate() {
    delete mainShader;
    glfwTerminate();
}

Engine::~Engine() {
    terminate();
}

void Engine::toggleWireframe() {
    wireframe = !wireframe;
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
    mainShader->use();
    mainShader->setBool("u_wireframe", wireframe);
}