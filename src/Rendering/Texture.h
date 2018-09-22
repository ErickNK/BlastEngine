//
// Created by erick on 8/12/18.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H


#include <string>
#include <GL/glew.h>
#include "../Common/CommonValues.h"

class Texture {
public:
    /**
     * Empty Constructor
     * */
    Texture();

    /**
     * Constructor. Load a texture from storage.
     * */
	explicit Texture(GLuint texture,TextureTypeEnum typeName):m_texture(texture), m_textureType(typeName){}

	Texture(std::string fileLocation, TextureTypeEnum typeName);

	Texture(std::string path, std::string directory, TextureTypeEnum typeName);

    /**
    * Destructor
    * */
    virtual ~Texture();

    /**
     * Instruct the processor to start using the textures provided. Maximum
     * textures that can be binded are 32.
     * */
    void Bind(unsigned int unit);

    /**
     * Delete Texture
     * */
	void Delete();
	/**
     * Load the texture provided by the fileLocation without an alpha channel
     * */
    bool LoadTexture();

	/**
	* Get the path of the texture.
	*/
	std::string GetFileLocation() { return m_fileLocation; }

	/**
	* Get the type of the texture.
	*/
	TextureTypeEnum GetTextureType() { return m_textureType; }

protected:
private:
    /**
     * The id to the texture created by the system. (like a reference/link)
     * */
    GLuint m_texture;

    /**
     * width and height of texture.
     * */
    int height = 0, width = 0, bitDepth = 0;

    /**
     * Location of texture to load.
     * */
    std::string m_fileLocation;

	/**
	* Type of texture to load.
	* */
	TextureTypeEnum m_textureType;
};


#endif //OPENGL_TEXTURE_H
