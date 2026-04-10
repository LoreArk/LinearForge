#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Entity.hpp"
#include "LightComponent.hpp"
#include "TransformComponent.h"
#include "Shader.hpp"

class LightSystem {
public:
    static constexpr int MAX_LIGHTS = 8;

    static void update(std::vector<std::unique_ptr<Entity>>& entities, Shader* shader) {
        int count = 0;

        for (auto& entity : entities) {
            if (!entity->active) continue;
            if (count >= MAX_LIGHTS) break;

            auto* lc = entity->getComponent<LightComponent>();
            if (!lc) continue;

            auto* tc = entity->getComponent<TransformComponent>();
            std::string b = "u_lights[" + std::to_string(count) + "]";

            shader->setVec3 (b + ".position",  tc ? tc->position : glm::vec3(0.0f));
            shader->setVec3 (b + ".color",     lc->color);
            shader->setFloat(b + ".intensity", lc->intensity);
            shader->setInt  (b + ".type",      (int)lc->type);
            count++;
        }

        shader->setInt("u_lightCount", count);
    }
};