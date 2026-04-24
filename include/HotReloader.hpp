#pragma once
#include <string>
#include <filesystem>
#include <iostream>
#include "Scene.hpp"
#include "SceneLoader.hpp"
#include "MeshLibrary.hpp"

class HotReloader {
public:
    HotReloader(const std::string& loadPath,
                const std::string& watchPath,
                Scene& scene,
                MeshLibrary& meshLib)
        : loadPath(loadPath), watchPath(watchPath),
          scene(scene), meshLib(meshLib)
    {
        reload();
        lastWrite = std::filesystem::last_write_time(watchPath);
    }

    void update() {
        try {
            auto currentWrite = std::filesystem::last_write_time(watchPath);
            if (currentWrite != lastWrite) {
                lastWrite = currentWrite;
                std::cout << "HotReloader: reloading..." << std::endl;

                // Copia il file sorgente nella build prima di ricaricare
                std::filesystem::copy_file(
                    watchPath, loadPath,
                    std::filesystem::copy_options::overwrite_existing
                );

                reload();
            }
        } catch (std::filesystem::filesystem_error& e) {
            std::cerr << "HotReloader: " << e.what() << std::endl;
        }
    }

private:
    std::string loadPath;
    std::string watchPath;
    Scene& scene;
    MeshLibrary& meshLib;
    std::filesystem::file_time_type lastWrite;

    void reload() {
        scene.clear();
        SceneLoader::load(loadPath, scene, meshLib);
    }
};
