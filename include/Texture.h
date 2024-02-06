#pragma once
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <string>
#include "stb_image.h";

class Texture {
public:
    // Constructor
    Texture();
    // Destructor
    ~Texture();
    // Loads and sets up an actual texture
    unsigned int LoadTexture(const std::string filepath);
    // slot tells us which slot we want to bind to.
    // We can have multiple slots. By default, we
    // will set our slot to 0 if it is not specified.
    void Bind(unsigned int slot = 0) const;
    // Be done with our texture
    void Unbind();
    //get ID
    GLuint GetID();
private:
    // Store a unique ID for the texture
    unsigned int m_textureID;
    // Filepath to the image loaded
    std::string m_filepath;
    // Store whatever image data inside of our texture class.
    //Image* m_image;
};

#endif