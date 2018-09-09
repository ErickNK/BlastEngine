#include <utility>

//
// Created by erick on 8/24/18.
//

#include "DirectionalLight.h"
#include "../../Core/CoreEngine.h"

DirectionalLight::DirectionalLight() :
    Light(),
    direction(glm::vec3(0.0f,-1.0f,0.0f))
{
    lightProjection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

DirectionalLight::DirectionalLight(
        glm::vec3 color,
        glm::vec3 direction,
        GLfloat ambientIntensity, GLfloat diffuseIntensity,
        GLfloat shadowWidth, GLfloat shadowHeight,
        glm::mat4 lightProj) :
    Light(color,ambientIntensity,diffuseIntensity,shadowWidth,shadowHeight),
    direction(glm::normalize(direction))
{
    lightProjection = lightProj;
}

DirectionalLight::~DirectionalLight() = default;

void DirectionalLight::UseLight(std::map<std::string, GLint>& m_uniforms,int shadowTextureUnit) {

    //Start using Lights shadow map
    shadowMap->UseShadowMap(shadowTextureUnit);

    //Set shadowTextureUnit
    glUniform1i(m_uniforms["directionalLight.shadowMap"], shadowTextureUnit);

    //Set Light Space
    glUniformMatrix4fv(m_uniforms["directionalLightSpace"], 1, GL_FALSE, glm::value_ptr(lightSpace));

    //Set Light Direction
    glUniform3f(m_uniforms["directionalLight.direction"],direction.x,direction.y,direction.z);

    //Set Light Color
    glUniform3f(m_uniforms["directionalLight.base.colour"],color.x,color.y,color.z);

    //Set Ambient Intensity
    glUniform1f(m_uniforms["directionalLight.base.ambientIntensity"],ambientIntensity);

    //Set Diffuse Intensity
    glUniform1f(m_uniforms["directionalLight.base.diffuseIntensity"],diffuseIntensity);
}

void DirectionalLight::SetupLightSpace(std::map<std::string, GLint>& m_uniforms, GLuint shaderProgram) {
	//Calculate Light space
	lightSpace = lightProjection * glm::lookAt(-direction,glm::vec3(0.0f,1.0f,1.0f),glm::vec3(0.0f,1.0f,0.0f));

	//Set Light Space
    m_uniforms["directionalLightSpace"] = glGetUniformLocation(shaderProgram, "directionalLightSpace");
	glUniformMatrix4fv(m_uniforms["directionalLightSpace"], 1, GL_FALSE, glm::value_ptr(lightSpace));
}

void DirectionalLight::SetupUniforms(std::map<std::string, GLint>& m_uniforms,GLuint shaderProgram) {

    m_uniforms["directionalLightSpace"] =
			glGetUniformLocation(shaderProgram, "directionalLightSpace");

    m_uniforms["directionalLight.shadowMap"] =
			glGetUniformLocation(shaderProgram, "directionalLight.shadowMap");

    m_uniforms["directionalLight.direction"] =
            glGetUniformLocation(shaderProgram, "directionalLight.direction");

    m_uniforms["directionalLight.base.colour"] =
            glGetUniformLocation(shaderProgram, "directionalLight.base.colour");

    m_uniforms["directionalLight.base.ambientIntensity"] =
            glGetUniformLocation(shaderProgram, "directionalLight.base.ambientIntensity");

    m_uniforms["directionalLight.base.diffuseIntensity"] =
            glGetUniformLocation(shaderProgram, "directionalLight.base.diffuseIntensity");
}

void DirectionalLight::AddToEngine(CoreEngine *engine) {
    engine->GetRenderingEngine()->AddDirectionalLight(this);
}
