#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#include "Scene.hpp"
#include <vector>

class Engine {
public:
    Engine();
    ~Engine();

    bool init(int width, int height, const char* title);
    bool isRunning();
    void update();
    void render();
    void terminate();

    float getDeltaTime() const { return deltaTime; }

    Scene* createScene() {
        delete currentScene;
        currentScene = new Scene();
        return currentScene;
    }
    Scene* getScene() { return currentScene; }
    
    Shader* mainShader;
private:
    GLFWwindow* window;
    
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    void initOpenGL();

    Scene* currentScene = nullptr;
};