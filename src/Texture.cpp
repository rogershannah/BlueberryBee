#include "Texture.h"
#include <iostream>

Texture::Texture()
{
}

Texture::~Texture()
{
    // Delete our texture from the GPU
    glDeleteTextures(1, &m_textureID);

    //// Delete our image
    //if (m_image != nullptr) {
    //    delete m_image;
    //}
}

unsigned int Texture::LoadTexture(const std::string filepath)
{
    m_filepath = filepath;
    // load and create a texture 
   // -------------------------
    glGenTextures(1, &m_textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, m_textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << filepath << std::endl;
        stbi_image_free(data);
    }

    return m_textureID;
    
}

void Texture::Bind(unsigned int slot) const
{
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::GetID()
{
    return m_textureID;
}
