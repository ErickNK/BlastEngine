#include <cassert>
#include <iostream>
#include <fstream>
#include "Texture.h"

Texture::Texture() = default;

Texture::Texture(std::string fileLocation, TextureTypeEnum typeName) :
	m_fileLocation(fileLocation),
	m_textureType(typeName){
    LoadTexture();
}

Texture::Texture(std::string path,std::string directory, TextureTypeEnum typeName) :
	m_fileLocation(directory + '/' + path), 
	m_textureType(typeName) {
	LoadTexture();
}

bool Texture::LoadTexture(){
    // One char is equal to a byte. Useful for representing - image array, string.
    // When its a pointer it acts like an array
//	std::ifstream in(m_fileLocation, std::ifstream::ate | std::ifstream::binary);
	unsigned char * texture_data = stbi_load(m_fileLocation.c_str(),&width,&height,&bitDepth, 0);

    if(texture_data == nullptr){
        std::cerr << "Error: Texture loading failed for:"<< m_fileLocation << std::endl;
        return false;
    }

	GLenum format;
	if (bitDepth == 1)
		format = GL_RED;
	else if (bitDepth == 3)
		format = GL_RGB;
	else if (bitDepth == 4)
		format = GL_RGBA;

    glGenTextures(1,&m_texture); //Generate texture unit (Like a buffer)
		glBindTexture(GL_TEXTURE_2D,m_texture);

			//WRAP filter
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

			//Overlap filter
			glTexParameterf(
					GL_TEXTURE_2D,
					GL_TEXTURE_MIN_FILTER, // Applied when texture is further away/smaller
					GL_LINEAR_MIPMAP_LINEAR
			);
			glTexParameterf(
					GL_TEXTURE_2D,
					GL_TEXTURE_MAG_FILTER, // Applied when texture is closer/bigger
					GL_LINEAR
			);

			glTexImage2D(
					GL_TEXTURE_2D, //Texture target
					0, // Mipmap Level
					format, // Format of how it will be stored
					width,height, // Width and height of the image/data being loaded
					0, // Should always be 0, Legacy option that defines whether to add borders to the texture.
					format, // Format of the data being loaded
					GL_UNSIGNED_BYTE, // Data type of the values
					texture_data // Data itself
			);

			glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,0);

	stbi_image_free(texture_data);

    return true;
}

Texture::~Texture() {
    //glDeleteTextures(1,&m_texture);
    //m_texture = static_cast<GLuint>(width = height = bitDepth = 0);
}

void Texture::Bind(unsigned int unit) {
    assert(unit >= 0 && unit <= 31);

    // Activate the texture unit the texture was loaded into
    glActiveTexture(GL_TEXTURE0 + unit);

    // Bind the texture for use
    glBindTexture(GL_TEXTURE_2D,m_texture);
}

void Texture::Delete() {
	//glDeleteTextures(1,&m_texture);
	//m_texture = static_cast<GLuint>(width = height = bitDepth = 0);
}



