#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Entity.hpp"
#include "InputComponent.hpp"
#include "Camera.hpp"

class CameraSystem {
public:
    static constexpr float SPEED       = 3.0f;
    static constexpr float SENSITIVITY = 0.1f;

    // absolute yaw and pitch
    static inline float yaw   = -90.0f;
    static inline float pitch =   0.0f;

    static void update(std::vector<std::unique_ptr<Entity>>& entities,
                       Camera& camera,
                       float deltaTime)
    {
        for (auto& entity : entities) {
            if (!entity->active) continue;
            auto* ic = entity->getComponent<InputComponent>();
            if (!ic) continue;

            // ── Mouse Rotation ───────────────────────────────────
            if (ic->mouseDelta != glm::vec2(0.0f)) {
                yaw   +=  ic->mouseDelta.x * SENSITIVITY;
                pitch += -ic->mouseDelta.y * SENSITIVITY;

                // Clamp pitch
                if (pitch >  89.0f) pitch =  89.0f;
                if (pitch < -89.0f) pitch = -89.0f;
            }

            // Calculate front from abs angles
            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            front = glm::normalize(front);

            glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0,1,0)));
            glm::vec3 up    = glm::vec3(0,1,0);

            // ── Movement ─────────────────────────────────────────
            float vel = SPEED * deltaTime;
            if (ic->forward)  camera.position += front * vel;
            if (ic->backward) camera.position -= front * vel;
            if (ic->right)    camera.position += right * vel;
            if (ic->left)     camera.position -= right * vel;
            if (ic->up)       camera.position += up    * vel;
            if (ic->down)     camera.position -= up    * vel;

            camera.front = front;
        }
    }
};