#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component.hpp"

class TransformComponent : public Component {
public:
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale    = glm::vec3(1.0f);
    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

    glm::vec3 spinSpeed = glm::vec3(0.0f);

    glm::mat4 getMatrix() const {
        glm::mat4 m = glm::mat4(1.0f); // matrice identità come punto di partenza

        m = glm::translate(m, position);           // 3. sposta
        m = m * glm::mat4_cast(rotation);          // 2. ruota (converte quat → mat4)
        m = glm::scale(m, scale);                  // 1. scala

        return m;
    }

    void rotate(float degrees, glm::vec3 axis) {
        glm::quat delta = glm::angleAxis(
            glm::radians(degrees), 
            glm::normalize(axis)
        );
        rotation = delta * rotation;
    }

};