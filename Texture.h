//
// Created by erick on 8/12/18.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H


#include <string>
#include <GL/glew.h>

class Texture {
public:
    /**
     * Empty Constructor
     * */
    Texture();

    /**
     * Constructor. Load a texture from storage.
     * */
    explicit Texture(const std::string &fileLocation);

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
     * Load the texture provided by the fileLocation
     * */
    void LoadTexture();

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
    const std::string m_fileLocation;
};


#endif //OPENGL_TEXTURE_H
