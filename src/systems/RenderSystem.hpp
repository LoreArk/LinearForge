// src/systems/RenderSystem.hpp
#pragma once
#include <vector>
#include <memory>
#include "Entity.hpp"
#include "RenderComponent.hpp"
#include "TransformComponent.h"
#include "MaterialComponent.hpp"
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
        shader->setVec3("u_viewPos",    camera.position);  // per specular

        for (auto& entity : entities) {
            if (!entity->active) continue;

            auto* rc = entity->getComponent<RenderComponent>();
            if (!rc) continue;

            // Transform
            auto* tc = entity->getComponent<TransformComponent>();
            glm::mat4 model = tc ? tc->getMatrix() : glm::mat4(1.0f);
            shader->setMat4("u_model", model);

            // Material
            auto* mc = entity->getComponent<MaterialComponent>();
            if (mc) {
                shader->setVec3 ("u_mat.color",     mc->color);
                shader->setFloat("u_mat.ambient",   mc->ambient);
                shader->setFloat("u_mat.diffuse",   mc->diffuse);
                shader->setFloat("u_mat.specular",  mc->specular);
                shader->setFloat("u_mat.shininess", mc->shininess);
            } else {
                // default 
                shader->setVec3 ("u_mat.color",     glm::vec3(0.8f));
                shader->setFloat("u_mat.ambient",   0.05f);
                shader->setFloat("u_mat.diffuse",   0.95f);
                shader->setFloat("u_mat.specular",  0.02f);
                shader->setFloat("u_mat.shininess", 4.0f);
            }

            rc->mesh->draw();
        }
    }
};