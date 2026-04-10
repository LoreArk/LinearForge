// Camera.hpp
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float fov, aspectRatio, nearPlane, farPlane;

    Camera(glm::vec3 position  = glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3 target    = glm::vec3(0.0f, 0.0f, 0.0f),
           float fov           = 45.0f,
           float aspectRatio   = 16.0f / 9.0f,
           float nearPlane     = 0.1f,
           float farPlane      = 100.0f)
        : position(position),
          front(glm::normalize(target - position)),  // get front from start target
          up(glm::vec3(0,1,0)),
          fov(fov), aspectRatio(aspectRatio),
          nearPlane(nearPlane), farPlane(farPlane) {}

    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + front, up);  // target = position + front
    }

    glm::mat4 getProjectionMatrix() const {
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }
};