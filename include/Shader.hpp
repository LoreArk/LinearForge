#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID; // L'ID del programma shader compilato

    // Il costruttore legge e costruisce lo shader
    Shader(const char* vertexPath, const char* fragmentPath);
    
    ~Shader() {
        if (ID) glDeleteProgram(ID);
    }

    // Attiva lo shader
    void use();
    
    // Funzioni utility per configurare gli uniform
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
};

#endif