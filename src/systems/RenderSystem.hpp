// include/systems/RenderSystem.hpp
#pragma once
#include <vector>
#include <memory>
#include "Entity.hpp"
#include "RenderComponent.hpp"
#include "TransformComponent.h"
#include "Shader.hpp"
#include "Camera.hpp"

class RenderSystem {
public:
    static void render(std::vector<std::unique_ptr<Entity>>& entities, 
                       Shader* shader, 
                       const Camera& camera) 
    {
        shader->setMat4("u_view",       camera.getViewMatrix());
        shader->setMat4("u_projection", camera.getProjectionMatrix());

        for (auto& entity : entities) {
            if (!entity->active) continue;

            auto* rc = entity->getComponent<RenderComponent>();
            auto* tc = entity->getComponent<TransformComponent>();
            if (!rc) continue;

            glm::mat4 model = tc ? tc->getMatrix() : glm::mat4(1.0f);
            shader->setMat4("u_model", model);
            rc->mesh->draw();
        }
    }
};