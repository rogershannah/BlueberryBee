#ifndef GLFWGRAPHICSPROGRAM_H
#define GLFWGRAPHICSPROGRAM_H

#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Shader.h"
#include "Texture.h"

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
    // Get Pointer to Window
    GLFWwindow* GetGLFWWindow();
    // Helper Function to Query OpenGL information.
    void GetOpenGLVersionInfo();
    // Generate any vertex buffers
    void GenerateBuffers();
    //void CreateAndLoadTexture();
    void Dummy();

private:
    // Screen dimension constants
    int m_screenHeight;
    int m_screenWidth;

    // file names
    //std::string objFile;
    //std::string mtlFile;

    // The window we'll be rendering to
    GLFWwindow* m_window;
    // OpenGL context
    //GLFW_GLContext m_openGLContext;
    // buffer ogjects
    unsigned int VBO, VAO, EBO;
    //vertex shader
    unsigned int m_vertexShader;
    //shader
    //unsigned int shader; //one for now
    Shader* m_shader;
    //texture
    Texture m_texture;


    //helper functions
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow* window);
    void updateInput();

    // Shader helpers
    //unsigned int CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    //unsigned int CompileShader(unsigned int type, const std::string& source);
    bool checkLinkStatus(GLuint programID);
};

#endif