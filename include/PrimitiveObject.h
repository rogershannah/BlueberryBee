#pragma once
#ifndef PRIMITIVEOBJECT_H
#define PRIMITIVEOBJECT_H

#include <Texture.h>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>

class PrimitiveObject
{
public:

    // constructor 
    PrimitiveObject();
    ~PrimitiveObject();


    void LoadShader(std::string vertex, std::string fragment);

    void LoadTexture(std::string fileName, std::string map, unsigned int slot);

    void GenerateBuffers();

    void Render();

    void Update(float w, float h);


    void Unbind();


    void setVBO(unsigned int vbo);


private:
    Texture m_diffuse;
    Texture m_specular;
    Texture m_emissive;
    Texture m_normal;
    std::map<std::string, unsigned int> textureMap;
    // buffer ogjects
    unsigned int VBO, VAO, EBO;
    Shader* m_shader;

    unsigned int quadVAO = 0;
    unsigned int quadVBO;
    void renderQuad();


};

#endif