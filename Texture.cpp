#include <cassert>
#include <iostream>
#include "Texture.h"
#include "stb_image.h"

Texture::Texture() = default;

Texture::Texture(const std::string &fileLocation) : m_fileLocation(fileLocation){
    LoadTexture();
}

void Texture::LoadTexture() {

    // One char is equal to a byte. Useful for representing - image array, string.
    // When its a pointer it acts like an array
    unsigned char* imageData = stbi_load(m_fileLocation.c_str(),&width,&height,&bitDepth,4);

    if(imageData == nullptr){
        std::cerr << "Error: Texture loading failed for:"<< m_fileLocation << std::endl;
    }

    glGenTextures(1,&m_texture); //Generate texture unit (Like a buffer)
    glBindTexture(GL_TEXTURE_2D,m_texture);

        //WRAP filter
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

        //Overlap filter
        glTexParameterf(
                GL_TEXTURE_2D,
                GL_TEXTURE_MIN_FILTER, // Applied when texture is further away/smaller
                GL_LINEAR
            );
        glTexParameterf(
                GL_TEXTURE_2D,
                GL_TEXTURE_MAG_FILTER, // Applied when texture is closer/bigger
                GL_LINEAR
            );

        glTexImage2D(
                GL_TEXTURE_2D, //Texture target
                0, // Mipmap Level
                GL_RGBA, // Format of how it will be stored
                width,height, // Width and height of the image/data being loaded
                0, // Should always be 0, Legacy option that defines whether to add borders to the texture.
                GL_RGBA, // Format of the data being loaded
                GL_UNSIGNED_BYTE, // Data type of the values
                imageData // Data itself
            );

        glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);

    stbi_image_free(imageData);
}

Texture::~Texture() {
    glDeleteTextures(1,&m_texture);
    m_texture = static_cast<GLuint>(width = height = bitDepth = 0);
}

void Texture::Bind(unsigned int unit) {
    assert(unit >= 0 && unit <= 31);

    // Activate the texture unit the texture was loaded into
    glActiveTexture(GL_TEXTURE0 + unit);

    // Bind the texture for use
    glBindTexture(GL_TEXTURE_2D,m_texture);
}



