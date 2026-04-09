#pragma once
#include <memory>
#include "Component.hpp"
#include "Mesh.hpp"

struct RenderComponent : public Component {
    std::shared_ptr<Mesh> mesh;
    RenderComponent(std::shared_ptr<Mesh> mesh) : mesh(mesh) {}
};