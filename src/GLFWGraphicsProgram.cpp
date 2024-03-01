#include "GLFWGraphicsProgram.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h" 
#include "Camera.h" 


bool firstMouse = true;
float lastX; 
float lastY; 
float fov = 45.0f;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame


//light source location
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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

    //callbacks
    glfwSetWindowUserPointer(m_window, reinterpret_cast<void*>(this));
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    //glfwSetScrollCallback(m_window, scroll_callback);


    // tell GLFW to capture our mouse
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
    glDeleteVertexArrays(1, &lightVAO);
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

    //create camera
    Camera::Instance().InitCamera(glm::vec3(0.0f, 0.0f, 3.0f));
    lastX = m_screenWidth / 2.0f;
    lastY = m_screenHeight / 2.0f;

    /*container.LoadShader("./shaders/multipleLightsVert.glsl", "./shaders/multipleLightsFrag.glsl");
    light.LoadShader("./shaders/lampVert.glsl", "./shaders/lampFrag.glsl");
    container.isTextured = true;*/

    //m_model.Init("./assets/planet.obj");
    //m_model.Init("./assets/backpack/backpack.obj");
    //m_model.LoadShader("./shaders/modelBasicVert.glsl", "./shaders/modelBasicFrag.glsl");
   

    woodFloor.LoadShader("./shaders/normalMappingVert.glsl", "./shaders/normalMappingFrag.glsl");
    // Setup geometry
   GenerateBuffers();


    return success;
}

void GLFWGraphicsProgram::Update()
{
    /*container.Update((float)m_screenWidth, (float)m_screenHeight);
    light.Update((float)m_screenWidth, (float)m_screenHeight);*/
    woodFloor.Update((float)m_screenWidth, (float)m_screenHeight);
}

void GLFWGraphicsProgram::Render()
{
    //// render
    //    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*container.Render();
    light.Render();*/
    woodFloor.Render();
    //m_model.Render((float)m_screenWidth, (float)m_screenHeight);

}

void GLFWGraphicsProgram::Loop()
{
    //createTextures();

    ////render loop
    while (!glfwWindowShouldClose(m_window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(m_window);
        Update(); //nothing yet
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
    glGenBuffers(1, &VBO);
    woodFloor.setVBO(VBO);
   // woodFloor.GenerateBuffers();
    /*woodFloor.LoadTexture("./assets/normal/brickwall.jpg",  0);
    woodFloor.LoadTexture("./assets/normal/brickwall_normal.jpg",  1);*/

    woodFloor.LoadTexture("./assets/normal/brickwall.jpg", "diffuseMap",  0);
    woodFloor.LoadTexture("./assets/normal/brickwall_normal.jpg", "normalMap", 1);
    //woodFloor.LoadTexture("./assets/wood.png",  0);
    /*light.setVBO(VBO);
    container.GenerateBuffers();
    container.LoadTexture("./assets/container2.png", 0);
    container.LoadTexture("./assets/container2_specular.png", 1);
    container.LoadTexture("./assets/matrix.jpg", 1);

    light.GenerateBuffers();*/
}

void GLFWGraphicsProgram::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLFWGraphicsProgram::processInput(GLFWwindow* window)
{
    //wireframe 
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    //blinn
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !woodFloor.blinnKeyPressed)
    {
        woodFloor.blinn = !woodFloor.blinn;
        woodFloor.blinnKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE)
    {
        woodFloor.blinnKeyPressed = false;
    }

    //navigation via key input
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        Camera::Instance().ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        Camera::Instance().ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        Camera::Instance().ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        Camera::Instance().ProcessKeyboard(RIGHT, deltaTime);

    //camera via mouse pos
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    mouse_callback(xpos, ypos);
}

//void GLFWGraphicsProgram::createTransformations()
//{
//}

void GLFWGraphicsProgram::createTextures()
{
    //container
    //// load textures (we now use a utility function to keep the code more organized)
    //// -----------------------------------------------------------------------------
    //std::string path = "./assets/container2.png";
    //m_texture.LoadTexture(path.c_str());
    //
    //path = "./assets/container2_specular.png";
    //m_texture2.LoadTexture(path.c_str());

    //// shader configuration
    //// --------------------
    //m_shader->Use();
    //m_shader->SetInt("material.diffuse", 0);
    //m_shader->SetInt("material.specular", 1);

    ///*container.LoadTexture("./assets/container2.png", 0);
    //container.LoadTexture("./assets/container2_specular.png", 1);*/

    //
    

}

void GLFWGraphicsProgram::mouse_callback(double xposIn, double yposIn)
{ 
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

   Camera::Instance().ProcessMouseMovement(xoffset, yoffset);
}

void GLFWGraphicsProgram::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera::Instance().ProcessMouseScroll(static_cast<float>(yoffset));
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
