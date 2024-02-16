#pragma once
#ifndef CUBE_H
#define CUBE_H

#include <Texture.h>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube
{
public:

    // constructor 
    Cube();
    ~Cube();
    void LoadShader(std::string vertex, std::string fragment);

    void LoadTexture(std::string fileName, unsigned int slot);

    void GenerateBuffers();

    void Render(glm::vec3 lpos, glm::vec3 vpos, glm::mat4 view);


    void Unbind();

    bool isTextured = false;

    void setVBO(unsigned int vbo);

private:
    Texture m_diffuse;
    Texture m_specular;
    // buffer ogjects
    unsigned int VBO, VAO, EBO;
    Shader* m_shader;



};

#endif