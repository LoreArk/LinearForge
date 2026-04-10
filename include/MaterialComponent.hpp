#pragma once
#include <glm/glm.hpp>
#include "Component.hpp"

struct MaterialComponent : public Component {
    glm::vec3 color     = glm::vec3(1.0f);

    float ambient   = 0.05f;
    float diffuse   = 0.95f;
    float specular  = 0.02f;
    float shininess = 4.0f;
};