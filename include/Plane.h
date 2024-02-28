#pragma once
#ifndef PLANE_H
#define PLANE_H

#include <Texture.h>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Plane
{
public:

    // constructor 
    Plane();
    ~Plane();
    void LoadShader(std::string vertex, std::string fragment);

    void LoadTexture(std::string fileName, unsigned int slot);
    void LoadTexture(std::string fileName,std::string map, unsigned int slot);

    void GenerateBuffers();

    void Render();

    void Update(float w, float h);


    void Unbind();


    void setVBO(unsigned int vbo);


    //settings
    bool blinn = false;
    bool blinnKeyPressed = false;

private:
    Texture m_diffuse;
    Texture m_specular;
    Texture m_emission;
    Texture m_normal;
    std::vector<Texture> textureVect;
    // buffer ogjects
    unsigned int VBO, VAO, EBO;
    Shader* m_shader;

    unsigned int quadVAO = 0;
    unsigned int quadVBO;
    void renderQuad();


};

#endif