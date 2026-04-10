#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>
#include "Mesh.hpp"

class MeshLibrary {
public:
    void add(const std::string& name, std::shared_ptr<Mesh> mesh) {
        meshes[name] = mesh;
    }

    std::shared_ptr<Mesh> get(const std::string& name) {
        auto it = meshes.find(name);
        if (it != meshes.end()) return it->second;
        std::cerr << "MeshLibrary: '" << name << "' not found\n";
        return nullptr;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;
};