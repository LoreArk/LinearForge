#pragma once
#include <memory>
#include "Mesh.hpp"

class PrimitiveMeshes {
public:

    // ── Cube ──────────────────────────────────────────────────────
    static std::shared_ptr<Mesh> cube() {
        return std::make_shared<Mesh>(
            std::vector<float>{
            //   x      y      z      nx     ny     nz
                // Front
               -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
               -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                // Back
                0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
               -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
               -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                // Left
               -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
               -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
               -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
               -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                // Right
                0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                // Up
               -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
               -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                // Down
               -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
               -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            },
            std::vector<unsigned int>{
                 0, 1, 2,  2, 3, 0,   // front
                 4, 5, 6,  6, 7, 4,   // back
                 8, 9,10, 10,11, 8,   // left
                12,13,14, 14,15,12,   // right
                16,17,18, 18,19,16,   // up
                20,21,22, 22,23,20,   // down
            },
            6
        );
    }

    // ── Plane ─────────────────────────────────────────────────────
    static std::shared_ptr<Mesh> plane() {
        return std::make_shared<Mesh>(
            std::vector<float>{
            //   x      y      z      nx    ny    nz
               -0.5f,  0.0f, -0.5f,  0.0f, 1.0f, 0.0f,
                0.5f,  0.0f, -0.5f,  0.0f, 1.0f, 0.0f,
                0.5f,  0.0f,  0.5f,  0.0f, 1.0f, 0.0f,
               -0.5f,  0.0f,  0.5f,  0.0f, 1.0f, 0.0f,
            },
            std::vector<unsigned int>{
                0, 1, 2,  2, 3, 0,
            },
            6
        );
    }

    // ── Pyramid ──────────────────────────────────────────────────
    static std::shared_ptr<Mesh> pyramid() {
        return std::make_shared<Mesh>(
            std::vector<float>{
            //   x      y      z      nx      ny      nz
                // front face
               -0.5f, -0.5f,  0.5f,  0.0f,   0.447f,  0.894f,
                0.5f, -0.5f,  0.5f,  0.0f,   0.447f,  0.894f,
                0.0f,  0.5f,  0.0f,  0.0f,   0.447f,  0.894f,
                // right face
                0.5f, -0.5f,  0.5f,  0.894f, 0.447f,  0.0f,
                0.5f, -0.5f, -0.5f,  0.894f, 0.447f,  0.0f,
                0.0f,  0.5f,  0.0f,  0.894f, 0.447f,  0.0f,
                // back face
                0.5f, -0.5f, -0.5f,  0.0f,   0.447f, -0.894f,
               -0.5f, -0.5f, -0.5f,  0.0f,   0.447f, -0.894f,
                0.0f,  0.5f,  0.0f,  0.0f,   0.447f, -0.894f,
                // left face
               -0.5f, -0.5f, -0.5f, -0.894f, 0.447f,  0.0f,
               -0.5f, -0.5f,  0.5f, -0.894f, 0.447f,  0.0f,
                0.0f,  0.5f,  0.0f, -0.894f, 0.447f,  0.0f,
                // base
               -0.5f, -0.5f,  0.5f,  0.0f,  -1.0f,   0.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  -1.0f,   0.0f,
                0.5f, -0.5f, -0.5f,  0.0f,  -1.0f,   0.0f,
               -0.5f, -0.5f, -0.5f,  0.0f,  -1.0f,   0.0f,
            },
            std::vector<unsigned int>{
                 0, 1, 2,          // front
                 3, 4, 5,          // right
                 6, 7, 8,          // back
                 9,10,11,          // left
                12,13,14, 14,15,12 // base
            },
            6
        );
    }
};