//
// Created by erick on 8/25/18.
//

#include "SpotLight.h"
#include "../Camera.h"
#include "../../Core/CoreEngine.h"

SpotLight::SpotLight():
    PointLight(),
    direction(glm::vec3(0.0f,-1.0f, 0.0f)),
    edge(0.0f),  procEdge(cosf(glm::radians(edge)))
{
    m_type = SPOT_LIGHT;
}

SpotLight::SpotLight(
    glm::vec3 color, glm::vec3 position, glm::vec3 direction,
    GLfloat ambientIntensity, GLfloat diffuseIntensity,
    GLfloat constant, GLfloat linear, GLfloat quadratic,
    GLfloat edge, GLfloat shadowWidth, GLfloat shadowHeight) :
    PointLight(
            color, position,
            ambientIntensity, diffuseIntensity,
            constant, linear, quadratic,
            shadowWidth,shadowHeight
            ),
    direction(direction), edge(edge), procEdge(cosf(glm::radians(edge)))
{
    m_type = SPOT_LIGHT;
}

SpotLight::~SpotLight() {}

void SpotLight::UseLight(std::map<std::string, GLint>& m_uniforms, int shadowTextureUnit) {

		//Start using Lights shadow map
		shadowMap->UseShadowMap(shadowTextureUnit);

		//Set shadowTextureUnit
		glUniform1i(m_uniforms["spotLight.shadowMap"], shadowTextureUnit);

        glUniform3f(m_uniforms["spotLight.base.position"],position.x,position.y,position.z);

        glUniform3f(m_uniforms["spotLight.dir"],direction.x,position.y,position.z);

        glUniform1f(m_uniforms["spotLight.edge"],procEdge);

        glUniform1f(m_uniforms["spotLight.base.attenuationConstant"],constant);

        glUniform1f(m_uniforms["spotLight.base.attenuationLinear"],linear);

        glUniform1f(m_uniforms["spotLight.base.attenuationQuadratic"],quadratic);

        glUniform3f(m_uniforms["spotLight.base.base.colour"],color.x,color.y,color.z);

        glUniform1f(m_uniforms["spotLight.base.base.ambientIntensity"],ambientIntensity);

        glUniform1f(m_uniforms["spotLight.base.base.diffuseIntensity"] ,diffuseIntensity);
}

void SpotLight::SetAsFlashLight(const Camera& camera) {
        position = camera.getPosition();
        direction = camera.getDirection();
}

void SpotLight::SetupUniforms(std::map<std::string, GLint>& m_uniforms, GLuint shaderProgram) {
	m_uniforms["spotLight.shadowMap"] = glGetUniformLocation(shaderProgram, "spotLight.shadowMap");

	m_uniforms["spotLight.base.base.colour"] = glGetUniformLocation(shaderProgram, "spotLight.base.base.colour");

	m_uniforms["spotLight.base.base.ambientIntensity"] = glGetUniformLocation(shaderProgram, "spotLight.base.base.ambientIntensity");

	m_uniforms["spotLight.base.base.diffuseIntensity"] = glGetUniformLocation(shaderProgram, "spotLight.base.base.diffuseIntensity");

	m_uniforms["spotLight.base.position"] = glGetUniformLocation(shaderProgram, "spotLight.base.position");

	m_uniforms["spotLight.dir"] = glGetUniformLocation(shaderProgram, "spotLight.dir");

	m_uniforms["spotLight.edge"] = glGetUniformLocation(shaderProgram, "spotLight.edge");

	m_uniforms["spotLight.base.attenuationConstant"] = glGetUniformLocation(shaderProgram, "spotLight.base.attenuationConstant");

	m_uniforms["spotLight.base.attenuationLinear"] = glGetUniformLocation(shaderProgram, "spotLight.base.attenuationLinear");

	m_uniforms["spotLight.base.attenuationQuadratic"] = glGetUniformLocation(shaderProgram, "spotLight.base.attenuationQuadratic");

}