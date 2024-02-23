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

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  -1.0f),
    glm::vec3(2.0f,  5.0f, -1.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -1.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -3.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.0f,  0.0f, -3.0f)
};

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

void Cube::Render(glm::vec3 vpos, glm::mat4 view)
{
    /*glm::vec3 lightColor;
    lightColor.x = sin(glfwGetTime() * 2.0f);
    lightColor.y = sin(glfwGetTime() * 0.7f);
    lightColor.z = sin(glfwGetTime() * 1.3f);

    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);*/

    /*lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
    lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;*/

    // render
    //    // ------
    //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // be sure to activate shader when Setting uniforms/drawing objects
    m_shader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)720 / (float)720, 0.1f, 100.0f);
    if (isTextured) {

        ////m_shader->SetVec3("light.position", lightPos);
        //m_shader->SetVec3("light.position", vpos); //from camera for flashlight effect
        //m_shader->SetVec3("light.direction", Camera::Instance().GetFront());
        //m_shader->SetFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        //m_shader->SetFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
        //m_shader->SetVec3("viewPos", vpos);

        //// light properties
        //m_shader->SetVec3("light.ambient", 0.1f, 0.1f, 0.1f);
        //m_shader->SetVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
        ///*m_shader->SetVec3("light.ambient", ambientColor);
        //m_shader->SetVec3("light.diffuse", diffuseColor);*/
        //m_shader->SetVec3("light.specular", 1.0f, 1.0f, 1.0f);

        //m_shader->SetFloat("light.constant", 1.0f);
        //m_shader->SetFloat("light.linear", 0.09f);
        //m_shader->SetFloat("light.quadratic", 0.032f);

        //// material properties
        //m_shader->SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
        //m_shader->SetFloat("material.shininess", 64.0f);

        //// view/projection transformations


        //m_shader->SetMat4("projection", projection, true);
        //m_shader->SetMat4("view", view, true);
        // be sure to activate shader when Setting uniforms/drawing objects
        m_shader->Use();
        m_shader->SetVec3("viewPos", Camera::Instance().GetPosition());
        m_shader->SetFloat("material.shininess", 32.0f);

        /*
           Here we Set all the uniforms for the 5/6 types of lights we have. We have to Set them manually and index
           the proper PointLight struct in the array to Set each uniform variable. This can be done more code-friendly
           by defining light types as classes and Set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        // directional light
        m_shader->SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        m_shader->SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        m_shader->SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        m_shader->SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        m_shader->SetVec3("pointLights[0].position", pointLightPositions[0]);
        m_shader->SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        m_shader->SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        m_shader->SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        m_shader->SetFloat("pointLights[0].constant", 1.0f);
        m_shader->SetFloat("pointLights[0].linear", 0.09f);
        m_shader->SetFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        m_shader->SetVec3("pointLights[1].position", pointLightPositions[1]);
        m_shader->SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        m_shader->SetVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        m_shader->SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        m_shader->SetFloat("pointLights[1].constant", 1.0f);
        m_shader->SetFloat("pointLights[1].linear", 0.09f);
        m_shader->SetFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        m_shader->SetVec3("pointLights[2].position", pointLightPositions[2]);
        m_shader->SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        m_shader->SetVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        m_shader->SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        m_shader->SetFloat("pointLights[2].constant", 1.0f);
        m_shader->SetFloat("pointLights[2].linear", 0.09f);
        m_shader->SetFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        m_shader->SetVec3("pointLights[3].position", pointLightPositions[3]);
        m_shader->SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        m_shader->SetVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        m_shader->SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        m_shader->SetFloat("pointLights[3].constant", 1.0f);
        m_shader->SetFloat("pointLights[3].linear", 0.09f);
        m_shader->SetFloat("pointLights[3].quadratic", 0.032f);
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
        for (unsigned int i = 0; i < 10; i++)
        {
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_shader->SetMat4("model", model, true);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //// bind diffuse map
        m_diffuse.Bind(0);
        m_specular.Bind(1);
    }
    else {
        model = glm::mat4(1.0f); //reSet model
        m_shader->Use();
        m_shader->SetVec3("objectColor", 1.0f, 1.0f, 1.0f);
        m_shader->SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
        m_shader->SetMat4("projection", projection, true);
        m_shader->SetMat4("view", Camera::Instance().GetViewMatrix(), true);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        m_shader->SetMat4("model", model, true);

        glBindVertexArray(VAO);

        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            m_shader->SetMat4("model", model, true);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }

    // render the cube


}

void Cube::Unbind()
{
}

void Cube::setVBO(unsigned int vbo)
{
    VBO = vbo;
}


