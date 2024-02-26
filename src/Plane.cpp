#include "Plane.h"
#include "Camera.h"
#include <GLFW/glfw3.h>

// Set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
float planeVertices[] = {
    // positions            // normals         // texcoords
     10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
    -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
    -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

     10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
    -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
     10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
};

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
        m_shader->SetInt("material.diffuse", 0);
    case 1:
        m_specular.LoadTexture(fileName);
        m_shader->Use();
        m_shader->SetInt("material.specular", 1);
    case 2:
        m_emission.LoadTexture(fileName);
        m_shader->Use();
        m_shader->SetInt("material.emission", 2);
    }

}

void Plane::GenerateBuffers()
{

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);


}

void Plane::Render()
{
    m_shader->Use();

    m_diffuse.Bind(0);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Plane::Update(float w, float h)
{
    m_shader->Use();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), w/h, 0.1f, 100.0f);
    glm::mat4 view = Camera::Instance().GetViewMatrix();
    m_shader->SetMat4("projection", projection, true);
    m_shader->SetMat4("view", view, true);
    // set light uniforms
    m_shader->SetVec3("viewPos", Camera::Instance().GetPosition());
    m_shader->SetVec3("lightPos", glm::vec3(0.0f, 0.0f, 0.0f));
    m_shader->SetInt("blinn", blinn);
    

    std::cout << (blinn ? "Blinn-Phong" : "Phong") << std::endl;
}

void Plane::Unbind()
{
}

void Plane::setVBO(unsigned int vbo)
{
    VBO = vbo;
}


