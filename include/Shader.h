#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void Use();
    // utility uniform functions
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetVec3(const std::string& name, float x, float y, float z);
    void SetVec4(const std::string& name, const glm::vec4& value) const;

    void setMat4(const char* name, const glm::mat4& matrix, bool useShader);
private:
    void checkCompileErrors(unsigned int shader, std::string type);

};

#endif