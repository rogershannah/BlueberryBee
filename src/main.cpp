
#include <iostream>

#include "GLFWGraphicsProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// settings
const unsigned int SCR_WIDTH = 720;
const unsigned int SCR_HEIGHT = 720;

int main()
{
    std::cout << "starting BlueberryBee" << std::endl;
    // Create an instance of an object for a GLFWGraphicsProgram
    GLFWGraphicsProgram myGLFWGraphicsProgram(SCR_WIDTH, SCR_HEIGHT);
    // Print out some useful information
    //myGLFWGraphicsProgram.getOpenGLVersionInfo();
    // Run our program forever
    myGLFWGraphicsProgram.Loop();
    // When our program ends, it will exit scope, the
    // destructor will then be called and clean up the program.
    return 0;
}
