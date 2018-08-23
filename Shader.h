//
// Created by erick on 8/12/18.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Transform.h"
#include "Camera.h"

class Shader {
public:

    /**
     * Constructor
     * */
    Shader(const std::string& fileName);

    /**
     * Destructor
     * */
    virtual ~Shader();

    /**
     * Instruct the processor to start using the shaders provided by
     * the Shader class.
     * */
    void Bind();

    /**
    * Instruct the processor to stop using the shaders provided by
    * the Shader class.
    * */
    void UnBind();

    /**
     * Update some uniform data on GPU
     * */
    void UpdateModel(const Transform& transform);

    /**
     * Update some uniform data on GPU
     * */
    void UpdateView(const Camera& camera);

    /**
    * Update some uniform data on GPU
    * */
    void UpdateProjection(const glm::mat4& projection);

    /**
     * Load a shader from a file and return the whole file as string
     * */
    static std::string LoadShader(const std::string& fileName);

    /**
     * Check for errors in loading shaders
     * */
    static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

    /**
     * Compile the shader's source code and return it.
     * */
    static GLuint CreateShader(const std::string& text,GLenum shaderType);

protected:
private:

    /**
     * Uniforms used
     * */
    enum : unsigned int{
        VERTEX_SHADER,
        FRAGMENT_SHADER,
//        GEOMETRY_SHADER,

        NUM_SHADERS
    };

    /**
     * Uniforms used
     * */
    enum {
        MODEL_U,
        VIEW_U,
        PROJECTION_U,

        NUM_UNIFORMS
    };

    /**
     * Keeps track of where the program is, like a handle
     * */
    GLuint m_program;

    /**
     *  The shaders array.
     * */
    GLuint m_shaders[NUM_SHADERS];

    /**
     *  The uniforms array.
     * */
    GLuint m_uniforms[NUM_UNIFORMS];

};


#endif //OPENGL_SHADER_H
