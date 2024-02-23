#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Mesh.h"
#include "Shader.h"

class Model
{
public:

    Model();
    ~Model();

    void Init(std::string path);
    void LoadShader(std::string vertex, std::string fragment);
    void Render(float w, float h);
private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<TextureData> textures_loaded;
    Shader* m_shader;

    void draw();
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<TextureData> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);
    MaterialData loadMaterial(aiMaterial* mat);
    unsigned int TextureFromFile(const char* path, const std::string& directory);
};

#endif