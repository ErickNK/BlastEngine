//
// Created by erick on 8/12/18.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <string>
#include <map>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Transform.h"
#include "../Camera/Camera.h"
#include "../../Common/CommonValues.h"

class Shader {
public:

    /**
     * Constructor
     * */

    Shader() : m_type(BASIC_SHADER){};

    Shader(ShaderType type);

    Shader(std::map<int, std::string> shaderFiles,ShaderType type);

    /**
     * Initialize
     * */
    void Init();

    /**
     * Destructor
     * */
    virtual ~Shader();

    /**
     * Instruct the processor to start using the shaders provided by
     * the Shader class.
     * */
    virtual void Bind();

    /**
    * Instruct the processor to stop using the shaders provided by
    * the Shader class.
    * */
     virtual void UnBind();

    /**
     * Update some uniform data on GPU
     * */
    void UpdateModel(const Transform& transform);

    /**
     * Update some uniform data on GPU
     * */
    void UpdateView(const glm::mat4& view);

    /**
     * Activate a clipping plane.
     * */
    void ActivateClipPlane(int id, const glm::vec4& plane);

    /**
     * Deactivate a clipping plane.
     * */
    void DeactivateClipPlane(int id);

    void Uniform1i(std::string name, int value);

    void Uniform3f(const char* string, GLfloat i, GLfloat i1, GLfloat i2);

    void Uniform4f(const char* string, GLfloat i, GLfloat i1, GLfloat i2, GLfloat i3);

    /**
     * Update some uniform data on GPU
     * */
    void UpdateCamera(const Camera &camera);

    /**
    * Update some uniform data on GPU
    * */
    void UpdateProjection(const glm::mat4& projection);

	/**
	* Update the normal Matrix
	* */
	void UpdateNormalMatrix(const glm::mat3& normalMatrix);

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
    static GLuint CreateShader(const std::string& text,std::string filename, GLenum shaderType);

    /**
     * Create needed uniforms
     * */
    virtual void CreateUniforms();

    /**
     * Validate the shader
     * */
    virtual void validateProgram();

    /**
     * Retrieve the list of created uniforms
     * */
    std::map<std::string, GLint>& getUniforms();

	std::vector<GLuint> getShaders();

    GLuint getShaderProgram();

    ShaderType getType();

    int getAvailableGlobalTextureUnit();

    int getAvailableDrawingTextureUnit();

    void resetGlobalTextureUnits();

    void resetDrawingTextureUnits();

    void Uniform2f(const char string[19], float d, float d1);

    void Uniform1f(const char string[27], GLfloat d);

    void UniformMatrix4fv(const char* string, const glm::mat4 &x4);

protected:
    /**
   * Keeps track of the last issued glabal texture unit. Global texture units
   * are kept with each render pass
   */
    int lastIssuedGlobalTextureUnit = -1;

    /**
    * Keeps track of the last issued drawing texture unit. Drawing texture units
    * are kept only within drawing of a mesh and its material.
    */
    int lastIssuedDrawingTextureUnit = MAX_GLOBAL_TEXTURE_UNITS + 0;

    /**
     *  Type of shader.
     * */
    ShaderType m_type;

	/**
	* A map of the type and filename of the shader files to load onto 
	* this shader program.
	* */
	std::map<int, std::string> m_shaderFiles;

    /**
     * Keeps track of where the program is, like a handle
     * */
    GLuint m_program{};

    /**
     *  The shaders array.
     * */
    std::vector<GLuint> m_shaders;

    /**
     *  The uniforms array.
     * */
    std::map<std::string, GLint> m_uniforms;
};


#endif //OPENGL_SHADER_H
