#pragma once
#include <glm/glm.hpp>
#include "Component.hpp"

enum class LightType {
    Point,
    Directional
};

struct LightComponent : public Component {
    LightType type      = LightType::Point;
    glm::vec3 color     = glm::vec3(1.0f);
    float     intensity = 1.0f;
};