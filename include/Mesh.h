#pragma once
#ifndef MESH_H
#define MESH_H


#include "Shader.h"
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct VertexData {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};


struct TextureData {
    unsigned int id;
    std::string type;
    std::string path;
};

struct MaterialData {
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    glm::vec3 Ambient;
    float Shininess;
};

class Mesh
{
public:

    // constructor 
    Mesh();
    Mesh(std::vector<VertexData> vertices, std::vector<unsigned int> indices, std::vector<TextureData> textures);

    ~Mesh();

    // mesh data
    std::vector<VertexData>       vertices;
    std::vector<unsigned int> indices;
    std::vector<TextureData>      textures;

    void Draw(Shader& shader);

private:

    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();

};

#endif