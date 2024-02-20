#pragma once
#ifndef LIGHTCASTER_H
#define LIGHTCASTER_H

#include <Texture.h>
#include <Shader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightCaster
{
public:

    // constructor 
    LightCaster();
    ~LightCaster();
    void LoadShader(std::string vertex, std::string fragment);

    void GenerateBuffers();

    void Render(glm::vec3 vpos, glm::mat4 view);

    void Unbind();

    bool isTextured = false;

    void setVBO(unsigned int vbo);

private:
    Texture m_diffuse;
    Texture m_specular;
    Texture m_emission;
    // buffer ogjects
    unsigned int VBO, VAO, EBO;
    Shader* m_shader;



};

#endif