#pragma once
#include <glm/glm.hpp>
#include "Component.hpp"

struct InputComponent : public Component {
    bool forward  = false;
    bool backward = false;
    bool left     = false;
    bool right    = false;
    bool up       = false;
    bool down     = false;

    glm::vec2 mouseDelta   = glm::vec2(0.0f); 
    glm::vec2 mousePos     = glm::vec2(0.0f);
    bool      firstMouse   = true;         
};