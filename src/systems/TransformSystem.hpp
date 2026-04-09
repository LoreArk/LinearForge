// include/systems/TransformSystem.hpp
#pragma once
#include <vector>
#include <memory>
#include "Entity.hpp"
#include "TransformComponent.h"

class TransformSystem {
public:
    static void update(std::vector<std::unique_ptr<Entity>>& entities, float deltaTime) {
        for (auto& entity : entities) {
            if (!entity->active) continue;

            auto* t = entity->getComponent<TransformComponent>();
            if (!t) continue;

            // logica: applica spinSpeed
            if (t->spinSpeed.x != 0) t->rotate(t->spinSpeed.x * deltaTime, {1,0,0});
            if (t->spinSpeed.y != 0) t->rotate(t->spinSpeed.y * deltaTime, {0,1,0});
            if (t->spinSpeed.z != 0) t->rotate(t->spinSpeed.z * deltaTime, {0,0,1});
        }
    }
};