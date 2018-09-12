//
// Created by erick on 8/24/18.
//

#include "PointLight.h"
#include "../../Core/CoreEngine.h"
#include <glm/gtx/component_wise.hpp>

PointLight::PointLight() :
    Light(POINT_LIGHT),
    m_attenuation(0.0075f,0.045f,1.0f){}

PointLight::PointLight(glm::vec3 color, glm::vec3 position,
                       GLfloat ambientIntensity, GLfloat diffuseIntensity,
					   glm::vec3 attenuation,
						GLfloat shadowWidth, GLfloat shadowHeight) :
    Light(POINT_LIGHT,color,ambientIntensity,diffuseIntensity,shadowWidth,shadowHeight),
	m_attenuation(attenuation)
{
	m_transform.SetPos(position);
	CalculateRange();
}
void PointLight::CalculateRange(){
	float a = m_attenuation.x;
	float b = m_attenuation.y;
	float c = m_attenuation.z - COLOR_DEPTH * diffuseIntensity * glm::compMax(color);
	m_range = (- b + sqrt(b * b - 4 * a * c)) / (2 * a);
}

void PointLight::UseLight(std::map<std::string, GLint>& m_uniforms, int shadowTextureUnit) {

	//Start using Lights shadow map
	shadowMap->UseShadowMap(shadowTextureUnit);

	//Set shadowTextureUnit
	glUniform1i(m_uniforms["pointLight.shadowMap"], shadowTextureUnit);

    glUniform3f(m_uniforms["pointLight.position"],m_transform.GetPos().x,m_transform.GetPos().y,m_transform.GetPos().z);

    glUniform1f(m_uniforms["pointLight.attenuationConstant"],m_attenuation.z);

    glUniform1f(m_uniforms["pointLight.attenuationLinear"],m_attenuation.y);

    glUniform1f(m_uniforms["pointLight.attenuationQuadratic"],m_attenuation.x);

    glUniform3f(m_uniforms["pointLight.base.colour"],color.x,color.y,color.z);

    glUniform1f(m_uniforms["pointLight.base.ambientIntensity"],ambientIntensity);

    glUniform1f(m_uniforms["pointLight.base.diffuseIntensity"],diffuseIntensity);

	glUniform1f(m_uniforms["pointLight.range"],m_range);
}

PointLight::~PointLight() = default;

void PointLight::SetupUniforms(std::map<std::string, GLint>& m_uniforms, GLuint shaderProgram) {

	m_uniforms["pointLight.shadowMap"] = glGetUniformLocation(shaderProgram, "pointLight.shadowMap");

	m_uniforms["pointLight.base.colour"] = glGetUniformLocation(shaderProgram, "pointLight.base.colour");

	m_uniforms["pointLight.base.ambientIntensity"] = glGetUniformLocation(shaderProgram, "pointLight.base.ambientIntensity");

	m_uniforms["pointLight.base.diffuseIntensity"] = glGetUniformLocation(shaderProgram, "pointLight.base.diffuseIntensity");

	m_uniforms["pointLight.position"] = glGetUniformLocation(shaderProgram, "pointLight.position");

	m_uniforms["pointLight.attenuationConstant"] = glGetUniformLocation(shaderProgram, "pointLight.attenuationConstant");

	m_uniforms["pointLight.attenuationLinear"] = glGetUniformLocation(shaderProgram, "pointLight.attenuationLinear");

	m_uniforms["pointLight.attenuationQuadratic"] = glGetUniformLocation(shaderProgram, "pointLight.attenuationQuadratic");

	m_uniforms["pointLight.range"] = glGetUniformLocation(shaderProgram, "pointLight.range");
}
