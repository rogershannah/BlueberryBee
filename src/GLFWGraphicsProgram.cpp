#include "GLFWGraphicsProgram.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
};


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
    else
    {
        std::cout << "No SDL, GLAD, or OpenGL, errors Detected\n\n";
    }
}

GLFWGraphicsProgram::~GLFWGraphicsProgram()
{

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

bool GLFWGraphicsProgram::InitGL()
{
    //Success flag
    bool success = true;


    // Setup shaders
    std::string vertexShader = LoadShader("./shaders/vert.glsl");
    std::string fragmentShader = LoadShader("./shaders/frag.glsl");

    shader = CreateShader(vertexShader, fragmentShader);

    // Setup geometry
    GenerateBuffers();
    // Use our shader
   // glUseProgram(shader);

    return success;
}

void GLFWGraphicsProgram::Update()
{
}

void GLFWGraphicsProgram::Render()
{
    // render
    //clear color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);

    //render triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void GLFWGraphicsProgram::Loop()
{
    //render loop
    while (!glfwWindowShouldClose(m_window))
    {
        // input
        // -----
        processInput(m_window);
        updateInput();
        Render();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

std::string GLFWGraphicsProgram::LoadShader(const std::string& fname)
{
    std::string result;
    std::string line;
    std::ifstream shaderFile(fname.c_str());

    if (shaderFile.is_open())
    {
        while (getline(shaderFile, line))
        {
            result += line + '\n';
        }
    }
    // Close file
    shaderFile.close();
    return result;

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
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
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

unsigned int GLFWGraphicsProgram::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    //create program
    unsigned int program = glCreateProgram();

    // compile shaders
    unsigned int vertShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    // link program
    //attach shaders
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    //link
    glLinkProgram(program);
    glValidateProgram(program);
    // statch and delete
    glDetachShader(program, vertShader);
    glDetachShader(program, fragShader);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    if (!CheckLinkStatus(program))
    {
        std::cout << "ERROR, shader did not link!\n";
    }

    return program;
}

unsigned int GLFWGraphicsProgram::CompileShader(unsigned int type, const std::string& source)
{
    // Compile our shaders
    // id is the type of shader (Vertex, fragment, etc.)
    unsigned int id;
    int result; //result of compilation

    if (type == GL_VERTEX_SHADER)
    {
        id = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == GL_FRAGMENT_SHADER)
    {
        id = glCreateShader(GL_FRAGMENT_SHADER);
    }
    const char* src = source.c_str();
    // The source of our shader
    glShaderSource(id, 1, &src, nullptr);
    // Now compile our shader
    glCompileShader(id);

    // check for shader compile errors
    int success;
    glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char infoLog[512];
        glGetShaderInfoLog(id, length, &length, infoLog);
        if (type == GL_VERTEX_SHADER)
        {
            std::cout << "ERROR: GL_VERTEX_SHADER compilation failed!\n"
                << infoLog << "\n";
        }
        else if (type == GL_FRAGMENT_SHADER)
        {
            std::cout << "ERROR: GL_FRAGMENT_SHADER compilation failed!\n"
                << infoLog << "\n";
        }
        // Reclaim our memory
        delete[] infoLog;
        // Delete our broken shader
        glDeleteShader(id);
        return 0;
    }
    return id;
}

bool GLFWGraphicsProgram::CheckLinkStatus(GLuint programID)
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
