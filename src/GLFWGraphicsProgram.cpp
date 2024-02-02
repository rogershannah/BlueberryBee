#include "GLFWGraphicsProgram.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>



GLFWGraphicsProgram::GLFWGraphicsProgram(int w, int h)
{ 
    bool success = true;
    //init window
    glfwInit();

    //Create window 
    m_window = glfwCreateWindow(w, h, "GL", NULL, NULL);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        //return -1;
        success = false;
    }
    glfwMakeContextCurrent(m_window);

    //init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;

        //return -1;
        success = false;
    }

    

}

GLFWGraphicsProgram::~GLFWGraphicsProgram()
{
    glfwTerminate();
}

bool GLFWGraphicsProgram::InitGL()
{
	return false;
}

void GLFWGraphicsProgram::Update()
{
}

void GLFWGraphicsProgram::Render()
{
}

void GLFWGraphicsProgram::Loop()
{
    //render loop
    while (!glfwWindowShouldClose(m_window))
    {
        // input
        processInput(m_window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    std::cout << "hit terminate" << std::endl;
}

GLFWwindow* GLFWGraphicsProgram::GetGLFWWindow()
{
	return nullptr;
}

void GLFWGraphicsProgram::GetOpenGLVersionInfo()
{
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
