#pragma once
#include <vector>
#include <memory>
#include <GLFW/glfw3.h>
#include "Entity.hpp"
#include "InputComponent.hpp"

class InputSystem {
public:
    static void update(std::vector<std::unique_ptr<Entity>>& entities, GLFWwindow* window) {
        for (auto& entity : entities) {
            if (!entity->active) continue;

            auto* ic = entity->getComponent<InputComponent>();
            if (!ic) continue;

            // Tastiera — polling
            ic->forward  = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
            ic->backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
            ic->left     = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
            ic->right    = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
            ic->up       = glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS;
            ic->down     = glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;

            // Mouse
            double mx, my;
            glfwGetCursorPos(window, &mx, &my);
            glm::vec2 currentPos(mx, my);

            if (ic->firstMouse) {
                ic->mousePos   = currentPos;
                ic->firstMouse = false;
            }

            ic->mouseDelta = currentPos - ic->mousePos;
            ic->mousePos   = currentPos;
        }
    }
};