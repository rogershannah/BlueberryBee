#include "GLFWGraphicsProgram.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};
unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
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

    m_shader = new Shader("./shaders/vert.glsl", "./shaders/frag.glsl");

    // Setup geometry
    GenerateBuffers();


    return success;
}

void GLFWGraphicsProgram::Update()
{
    //load texture
    GLuint Texture = m_texture.LoadTexture("./assets/container.jpg");
    GLuint Texture2 = m_texture2.LoadTexture("./assets/awesomeface.png");
    // Bind our texture in Texture Unit 0
    m_texture.Bind(0);
    m_texture2.Bind(1);

    // create transformations
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    // get matrix's uniform location and set matrix
    m_shader->Use();
    unsigned int transformLoc = glGetUniformLocation(m_shader->ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

void GLFWGraphicsProgram::Render()
{
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind Texture
    //glBindTexture(GL_TEXTURE_2D, m_texture.GetID());
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void GLFWGraphicsProgram::Loop()
{
    m_shader->Use();
    glUniform1i(glGetUniformLocation(m_shader->ID, "texture"), 0); // set it manually
    glUniform1i(glGetUniformLocation(m_shader->ID, "texture2"), 1); // set it manually

    //render loop
    while (!glfwWindowShouldClose(m_window))
    {
        // input
        // -----
        processInput(m_window);
        updateInput();
        Update();
        Render();

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
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

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
