#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "Entity.hpp"
#include "RenderComponent.hpp"
#include "Camera.hpp"
#include "LightSystem.hpp"
#include "CameraSystem.hpp"
#include "InputSystem.hpp"
#include "TransformSystem.hpp"
#include "RenderSystem.hpp"

class Shader;

class Scene {
public:

    Camera camera;

    void update(float deltaTime, GLFWwindow* window) {
        InputSystem::update(entities, window);          
        CameraSystem::update(entities, camera, deltaTime);
        TransformSystem::update(entities, deltaTime);   
    }

    void render(Shader* shader) {
        LightSystem::update(entities, shader);
        RenderSystem::render(entities, shader, camera);
    }

    Entity* addEntity() {
        entities.push_back(std::make_unique<Entity>());
        return entities.back().get();
    }

    void purge() {
        std::erase_if(entities, [](const std::unique_ptr<Entity>& e) {
            return !e->active;
        });
    }

private:
    std::vector<std::unique_ptr<Entity>> entities;
};