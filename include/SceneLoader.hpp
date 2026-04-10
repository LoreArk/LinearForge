#pragma once
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Scene.hpp"
#include "Entity.hpp"
#include "TransformComponent.h"
#include "RenderComponent.hpp"
#include "MaterialComponent.hpp"
#include "LightComponent.hpp"
#include "InputComponent.hpp"
#include "MeshLibrary.hpp"

using json = nlohmann::json;

class SceneLoader {
public:
    // Load JSON to populate the scene
    static bool load(const std::string& path, Scene& scene, MeshLibrary& meshLib) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "SceneLoader: cannot open " << path << std::endl;
            return false;
        }

        json data;
        try {
            file >> data;
        } catch (json::exception& e) {
            std::cerr << "SceneLoader: JSON parse error: " << e.what() << std::endl;
            return false;
        }

        for (auto& ejson : data["entities"]) {
            Entity* entity = scene.addEntity();

            // ── TransformComponent ────────────────────────────────
            if (ejson.contains("transform")) {
                auto& t = ejson["transform"];
                auto* tc = entity->addComponent<TransformComponent>();

                if (t.contains("position"))
                    tc->position = readVec3(t["position"]);
                if (t.contains("scale"))
                    tc->scale = readVec3(t["scale"]);
                if (t.contains("spin"))
                    tc->spinSpeed = readVec3(t["spin"]);
            }

            // ── RenderComponent + MaterialComponent ───────────────
            if (ejson.contains("mesh")) {
                std::string meshName = ejson["mesh"];
                auto mesh = meshLib.get(meshName);
                if (mesh)
                    entity->addComponent<RenderComponent>(mesh);
                else
                    std::cerr << "SceneLoader: mesh '" << meshName << "' not found\n";
            }

            if (ejson.contains("material")) {
                auto& m = ejson["material"];
                auto* mc = entity->addComponent<MaterialComponent>();

                if (m.contains("color"))    mc->color     = readVec3(m["color"]);
                if (m.contains("ambient"))  mc->ambient   = m["ambient"];
                if (m.contains("diffuse"))  mc->diffuse   = m["diffuse"];
                if (m.contains("specular")) mc->specular  = m["specular"];
                if (m.contains("shininess"))mc->shininess = m["shininess"];
            }

            // ── LightComponent ────────────────────────────────────
            if (ejson.contains("light")) {
                auto& l = ejson["light"];
                auto* lc = entity->addComponent<LightComponent>();

                if (l.contains("color"))     lc->color     = readVec3(l["color"]);
                if (l.contains("intensity")) lc->intensity = l["intensity"];
                if (l.contains("type")) {
                    std::string type = l["type"];
                    lc->type = (type == "directional") 
                               ? LightType::Directional 
                               : LightType::Point;
                }
            }

            // ── InputComponent ────────────────────────────────────
            if (ejson.contains("input") && ejson["input"] == true)
                entity->addComponent<InputComponent>();
        }

        return true;
    }

private:
    static glm::vec3 readVec3(const json& j) {
        return glm::vec3(j[0].get<float>(), j[1].get<float>(), j[2].get<float>());
    }
};