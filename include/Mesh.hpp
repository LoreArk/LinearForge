#pragma once
#include <glad/glad.h>
#include <vector>

class Mesh {
public:
    Mesh(const std::vector<float>& vertices, int stride);

    Mesh(const std::vector<float>& vertices, 
        const std::vector<unsigned int>& indices, 
        int stride);

    ~Mesh();

    void draw() const;

private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;
    int vertexCount  = 0;
    int indexCount   = 0; 
};