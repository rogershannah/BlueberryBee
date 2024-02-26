#include "Cube.h"
#include "Camera.h"
#include <GLFW/glfw3.h>

// Set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
float verts[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

glm::vec3 cubePosition = 
    glm::vec3(0.0f,  0.0f,  0.0f);


glm::vec3 pointLightPosition = 
    glm::vec3(1.7f,  1.0f,  -0.0f);
//light source location
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::LoadShader(std::string vertex, std::string fragment)
{
    m_shader = new Shader(vertex.c_str(), fragment.c_str());
}

void Cube::LoadTexture(std::string fileName, unsigned int slot)
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

void Cube::GenerateBuffers()
{

    if (isTextured) {
        //configure the cube's VAO (and VBO)
        glGenVertexArrays(1, &VAO);
        //glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

        glBindVertexArray(VAO);
        //position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

    }
    else {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

}

void Cube::Render()
{
    m_shader->Use();

    m_diffuse.Bind(0);
    m_specular.Bind(1);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}

void Cube::Update(float w, float h)
{
    

    m_shader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), w / h, 0.1f, 100.0f);
    if (isTextured) {
        m_shader->SetVec3("viewPos", Camera::Instance().GetPosition());
        m_shader->SetFloat("material.shininess", 32.0f);



        // directional light
        m_shader->SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        m_shader->SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        m_shader->SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        m_shader->SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        m_shader->SetVec3("pointLights[0].position", pointLightPosition);
        m_shader->SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        m_shader->SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        m_shader->SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        m_shader->SetFloat("pointLights[0].constant", 1.0f);
        m_shader->SetFloat("pointLights[0].linear", 0.09f);
        m_shader->SetFloat("pointLights[0].quadratic", 0.032f);
        // spotLight
        m_shader->SetVec3("spotLight.position", Camera::Instance().GetPosition());
        m_shader->SetVec3("spotLight.direction", Camera::Instance().GetFront());
        m_shader->SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        m_shader->SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        m_shader->SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        m_shader->SetFloat("spotLight.constant", 1.0f);
        m_shader->SetFloat("spotLight.linear", 0.09f);
        m_shader->SetFloat("spotLight.quadratic", 0.032f);
        m_shader->SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        m_shader->SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // view/projection transformations


        m_shader->SetMat4("projection", projection, true);
        m_shader->SetMat4("view", Camera::Instance().GetViewMatrix(), true);
        
        model = glm::translate(model, cubePosition);
        float angle = 0;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        m_shader->SetMat4("model", model, true);

        

    }
    else 
    {
        model = glm::mat4(1.0f); //reSet model
        m_shader->Use();
        m_shader->SetVec3("objectColor", 1.0f, 1.0f, 1.0f);
        m_shader->SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
        m_shader->SetMat4("projection", projection, true);
        m_shader->SetMat4("view", Camera::Instance().GetViewMatrix(), true);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        m_shader->SetMat4("model", model, true);

        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPosition);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        m_shader->SetMat4("model", model, true);
        
    }
}

void Cube::Unbind()
{
}

void Cube::setVBO(unsigned int vbo)
{
    VBO = vbo;
}


