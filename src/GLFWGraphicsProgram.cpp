#include "GLFWGraphicsProgram.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

GLFWGraphicsProgram::GLFWGraphicsProgram(int w, int h) : m_screenWidth(w), m_screenHeight(h)
{ 
    bool success = true;

    // glfw: initialize and configure
   // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, "LearnOpenGL", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        success = false;
    }
    glfwMakeContextCurrent(m_window);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

     // glad: load all OpenGL function pointers
     // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        success = false;
    }
    

    //Initialize OpenGL
    if (!InitGL())
    {
        std::cout << "Unable to initialize OpenGL!\n" << std::endl;
        success = false;
    }

    //print status
    if (!success)
    {
        std::cout << "Failed to initialize!\n";
    }
}

GLFWGraphicsProgram::~GLFWGraphicsProgram()
{

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

bool GLFWGraphicsProgram::InitGL()
{
    //Success flag
    bool success = true;

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    //build and compile shader
    m_shader = new Shader("./shaders/vert.glsl", "./shaders/frag.glsl");

    // Setup geometry
    GenerateBuffers();


    return success;
}

void GLFWGraphicsProgram::Update()
{

}

void GLFWGraphicsProgram::Render()
{
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

    createTransformations();

    m_texture.Bind(0);
    m_texture2.Bind(1);

    m_shader->Use();

    createTransformations();

    // render box45
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}

void GLFWGraphicsProgram::Loop()
{
    createTextures();
    m_shader->Use();
    m_shader->SetInt("texture1", 0);
    m_shader->SetInt("texture2", 1);

    //render loop
    while (!glfwWindowShouldClose(m_window))
    {
        // input
        // -----
        processInput(m_window);
        updateInput();
        Render();
        Update();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}


GLFWwindow* GLFWGraphicsProgram::GetGLFWWindow()
{
	return nullptr;
}

void GLFWGraphicsProgram::GetOpenGLVersionInfo()
{
}

void GLFWGraphicsProgram::GenerateBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void GLFWGraphicsProgram::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLFWGraphicsProgram::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void GLFWGraphicsProgram::updateInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }   

    
}
void GLFWGraphicsProgram::createTransformations()
{
    // create transformations
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)m_screenWidth / (float)m_screenHeight, 0.1f, 100.0f);
    // retrieve the matrix uniform locations
    unsigned int modelLoc = glGetUniformLocation(m_shader->ID, "model");
    unsigned int viewLoc = glGetUniformLocation(m_shader->ID, "view");
    // pass them to the shaders (3 different ways)
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    m_shader->setMat4("projection", projection, true);
}

void GLFWGraphicsProgram::createTextures()
{

    //load texture
    GLuint Texture = m_texture.LoadTexture("./assets/container.jpg");
    GLuint Texture2 = m_texture2.LoadTexture("./assets/awesomeface.png");
    // Bind our texture in Texture Unit 0
}

bool GLFWGraphicsProgram::checkLinkStatus(GLuint programID)
{
    int result;

    // This code is returning any Linker errors that may have occurred!
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &length);
        char* errorMessages = new char[length]; // Could also use alloca here.
        glGetProgramInfoLog(programID, length, &length, errorMessages);
        // Reclaim our memory
        std::cout << "ERROR in linking process " << errorMessages << "\n";
        delete[] errorMessages;
        return false;
    }
    return true;
}
