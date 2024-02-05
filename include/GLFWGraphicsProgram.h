#ifndef GLFWGRAPHICSPROGRAM_H
#define GLFWGRAPHICSPROGRAM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// The glad library helps setup OpenGL extensions.



// Purpose:
// This class sets up a full graphics program using GLFW
//
//
//
class GLFWGraphicsProgram {
public:

    // Constructor
    GLFWGraphicsProgram(int w, int h);
    // Desctructor
    ~GLFWGraphicsProgram();
    // Setup OpenGL
    bool InitGL();
    // Per frame update
    void Update();
    // Renders shapes to the screen
    void Render();
    // loop that runs forever
    void Loop();
    // load shaders
    void LoadShaders();
    // Get Pointer to Window
    GLFWwindow* GetGLFWWindow();
    // Helper Function to Query OpenGL information.
    void GetOpenGLVersionInfo();
    // Generate any vertex buffers
    void GenerateBuffers();

private:
    // Screen dimension constants
    int m_screenHeight;
    int m_screenWidth;
    // The window we'll be rendering to
    GLFWwindow* m_window;
    // OpenGL context
    //GLFW_GLContext m_openGLContext;
    // buffer ogjects
    unsigned int VBOs[2], VAOs[2];
    //vertex shader
    unsigned int m_vertexShader;
    //shader
    unsigned int m_shaderProgramOrange;
    unsigned int m_shaderProgramYellow;


    //helper functions
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow* window);
    void updateInput();
};

#endif