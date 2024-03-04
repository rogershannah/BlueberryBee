#include "Plane.h"
#include "Camera.h"
#include <GLFW/glfw3.h>

//// Set up vertex data (and buffer(s)) and configure vertex attributes
//   // ------------------------------------------------------------------
//float planeVertices[] = {
//    // positions            // normals         // texcoords
//     10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
//    -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
//    -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
//
//     10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
//    -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
//     10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
//};

Plane::Plane()
{
}

Plane::~Plane()
{
}

void Plane::LoadShader(std::string vertex, std::string fragment)
{
    m_shader = new Shader(vertex.c_str(), fragment.c_str());
}

void Plane::LoadTexture(std::string fileName, unsigned int slot)
{
    switch (slot) {
    case 0:
        m_diffuse.LoadTexture(fileName);
        m_shader->Use();
        m_shader->SetInt("diffuseMap", 0);
        std::cout << "diff id " << m_diffuse.GetID() << std::endl;
    case 1:
        m_normal.LoadTexture(fileName);
        m_shader->Use();
        m_shader->SetInt("normalMap", 1);
        std::cout << "norm id " << m_normal.GetID() << std::endl;
    /*case 2:
        m_emission.LoadTexture(fileName);
        m_shader->Use();
        m_shader->SetInt("material.emission", 2);*/
    }
    std::cout << fileName << " slot " << slot << std::endl;

}

void Plane::LoadTexture(std::string fileName, std::string map, unsigned int slot)
{
     if (map == "diffuseMap") {
        m_diffuse.LoadTexture(fileName);
        std::cout << "diff id " << m_normal.GetID() << std::endl;
    } else if (map == "specularMap") {
        m_specular.LoadTexture(fileName);
        std::cout << "m_specular id " << m_specular.GetID() << std::endl;
    }
    else if (map == "emissiveMap") {
        m_emissive.LoadTexture(fileName);
        std::cout << "m_emissive id " << m_emissive.GetID() << std::endl;
    }
    else if (map == "normalMap") {
        m_normal.LoadTexture(fileName);
        std::cout << "norm id " << m_normal.GetID() << std::endl;
    }
     textureMap[map] = slot;
     m_shader->Use();
     m_shader->SetInt(map, slot);
}

void Plane::GenerateBuffers()
{

    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    //glBindVertexArray(VAO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(2);
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glBindVertexArray(0);


}

void Plane::Render()
{
    m_shader->Use();

    std::map<std::string, unsigned int>::iterator it = textureMap.begin();

    // Iterate through the map and print the elements
    while (it != textureMap.end()) {
        if (it->first == "diffuseMap") {
            m_diffuse.Bind(it->second);
        }
        else if (it->first == "specularMap") {
            m_specular.Bind(it->second);
        }
        else if (it->first == "emissiveMap") {
            m_emissive.Bind(it->second);
        }
        else if (it->first == "normalMap") {
            m_normal.Bind(it->second);
        }
        ++it;
    }
    renderQuad();

}

void Plane::Update(float w, float h)
{
    m_shader->Use();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), w/h, 0.1f, 100.0f);
    glm::mat4 view = Camera::Instance().GetViewMatrix();
    m_shader->SetMat4("projection", projection, true);
    m_shader->SetMat4("view", view, true);
    // render normal-mapped quad
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0))); // rotate the quad to show normal mapping from multiple directions
    m_shader->SetMat4("model", model, true);
    m_shader->SetVec3("viewPos", Camera::Instance().GetPosition());
    m_shader->SetVec3("lightPos", glm::vec3(0.0f, 0.0f, 0.0f));
    

    //std::cout << (blinn ? "Blinn-Phong" : "Phong") << std::endl;
}

void Plane::Unbind()
{
}

void Plane::setVBO(unsigned int vbo)
{
    VBO = vbo;
}

void Plane::renderQuad()
{
    if (quadVAO == 0)
    {
        // positions
        glm::vec3 pos1(-1.0f, 1.0f, 0.0f);
        glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
        glm::vec3 pos3(1.0f, -1.0f, 0.0f);
        glm::vec3 pos4(1.0f, 1.0f, 0.0f);
        // texture coordinates
        glm::vec2 uv1(0.0f, 1.0f);
        glm::vec2 uv2(0.0f, 0.0f);
        glm::vec2 uv3(1.0f, 0.0f);
        glm::vec2 uv4(1.0f, 1.0f);
        // normal vector
        glm::vec3 nm(0.0f, 0.0f, 1.0f);

        // calculate tangent/bitangent vectors of both triangles
        glm::vec3 tangent1, bitangent1;
        glm::vec3 tangent2, bitangent2;
        // triangle 1
        // ----------
        glm::vec3 edge1 = pos2 - pos1;
        glm::vec3 edge2 = pos3 - pos1;
        glm::vec2 deltaUV1 = uv2 - uv1;
        glm::vec2 deltaUV2 = uv3 - uv1;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

        bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

        // triangle 2
        // ----------
        edge1 = pos3 - pos1;
        edge2 = pos4 - pos1;
        deltaUV1 = uv3 - uv1;
        deltaUV2 = uv4 - uv1;

        f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);


        bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);


        float quadVertices[] = {
            // positions            // normal         // texcoords  // tangent                          // bitangent
            pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
            pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
            pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

            pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
            pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
            pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
        };
        // configure plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


