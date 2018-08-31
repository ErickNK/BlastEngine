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

#include "Transform.h"
#include "Camera.h"
#include "CommonValues.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"

class Shader {
public:

    /**
     * Constructor
     * */
    Shader(std::map<int, std::string> shaderFiles);

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
    static GLuint CreateShader(const std::string& text,GLenum shaderType);

    /**
     * Create needed uniforms
     * */
    void CreateUniforms();

    /**
     * Retrieve the list of created uniforms
     * */
    GLint *getUniforms();

	std::vector<GLuint> getShaders();

    GLuint getShaderProgram();

    DirectionalLightUniforms* getDirectionalLightUniforms();

    void SetDirectionalLight(DirectionalLight *dLight);

    PointLightUniforms* getPointLightUniformsArray();

    void SetPointLights(PointLight *pLights, unsigned int lightCount);

    MaterialUniforms* getMaterialUniforms();

    void SetSpotLights(SpotLight *sLights, unsigned int lightCount);

protected:
private:
	/**
	* A map of the type and filename of the shader files to load onto 
	* this shader program.
	* */
	std::map<int, std::string> m_shaderFiles;

    /**
     * Keeps track of total amount of lights the shader has.
     * */
    int pointLightCount, spotLightCount;

    /**
     * Keeps track of where the program is, like a handle
     * */
    GLuint m_program;

    /**
     *  The shaders array.
     * */
    std::vector<GLuint> m_shaders;

    /**
     *  The uniforms array.
     * */
    GLint m_uniforms[NUM_UNIFORMS];

    /**
    *  The uniforms for a material.
    * */
    MaterialUniforms m_material;

    /**
     *  The uniforms for a Directional Light.
     * */
    DirectionalLightUniforms m_directional_light;

    /**
     *  The uniforms for Point Lights.
     * */
    PointLightUniforms m_point_lights[MAX_POINT_LIGHTS];

    /**
     *  The uniforms for Spot Lights.
     * */
    SpotLightUniforms m_spot_lights[MAX_SPOT_LIGHTS];

};


#endif //OPENGL_SHADER_H
