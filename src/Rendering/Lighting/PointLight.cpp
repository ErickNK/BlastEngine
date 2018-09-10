//
// Created by erick on 8/24/18.
//

#include "PointLight.h"
#include "../../Core/CoreEngine.h"

PointLight::PointLight() :
    Light(POINT_LIGHT), position(glm::vec3(5.0f,0.0f,0.0f)),
    constant(1.0f),linear(0.045f),quadratic(0.0075f){}

PointLight::PointLight(glm::vec3 color, glm::vec3 position,
                       GLfloat ambientIntensity, GLfloat diffuseIntensity,
                       GLfloat constant, GLfloat linear, GLfloat quadratic,
						GLfloat shadowWidth, GLfloat shadowHeight) :
    Light(POINT_LIGHT,color,ambientIntensity,diffuseIntensity,shadowWidth,shadowHeight),
    position(position),
    constant(constant),linear(linear),quadratic(quadratic){}


void PointLight::UseLight(std::map<std::string, GLint>& m_uniforms, int shadowTextureUnit) {

	//Start using Lights shadow map
	shadowMap->UseShadowMap(shadowTextureUnit);

	//Set shadowTextureUnit
	glUniform1i(m_uniforms["pointLight.shadowMap"], shadowTextureUnit);

    glUniform3f(m_uniforms["pointLight.position"],position.x,position.y,position.z);

    glUniform1f(m_uniforms["pointLight.attenuationConstant"],constant);

    glUniform1f(m_uniforms["pointLight.attenuationLinear"],linear);

    glUniform1f(m_uniforms["pointLight.attenuationQuadratic"],quadratic);

    glUniform3f(m_uniforms["pointLight.base.colour"],color.x,color.y,color.z);

    glUniform1f(m_uniforms["pointLight.base.ambientIntensity"],ambientIntensity);

    glUniform1f(m_uniforms["pointLight.base.diffuseIntensity"],diffuseIntensity);
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
}

/*
void PointLight::AddToEngine(CoreEngine *engine) {
    engine->GetRenderingEngine()->AddPointLight(this);
}
*/
