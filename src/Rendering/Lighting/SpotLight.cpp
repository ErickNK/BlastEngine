//
// Created by erick on 8/25/18.
//

#include "SpotLight.h"
#include "../Camera/Camera.h"
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
    glm::vec3 attenuation,
    GLfloat edge, GLfloat shadowWidth, GLfloat shadowHeight) :
    PointLight(
            color, position,
            ambientIntensity, diffuseIntensity,
            attenuation,
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

        glUniform3f(m_uniforms["spotLight.base.position"],m_transform.GetPos().x,m_transform.GetPos().y,m_transform.GetPos().z);

        glUniform3f(m_uniforms["spotLight.dir"],direction.x,direction.y,direction.z);

        glUniform1f(m_uniforms["spotLight.edge"],procEdge);

        glUniform1f(m_uniforms["spotLight.base.attenuationConstant"],m_attenuation.z);

        glUniform1f(m_uniforms["spotLight.base.attenuationLinear"],m_attenuation.y);

        glUniform1f(m_uniforms["spotLight.base.attenuationQuadratic"],m_attenuation.x);

        glUniform3f(m_uniforms["spotLight.base.base.colour"],color.x,color.y,color.z);

        glUniform1f(m_uniforms["spotLight.base.base.ambientIntensity"],ambientIntensity);

        glUniform1f(m_uniforms["spotLight.base.base.diffuseIntensity"] ,diffuseIntensity);

        glUniform1f(m_uniforms["spotLight.base.range"],m_range);

        glUniform1i(m_uniforms["allowCellShading"],m_allow_cell_shading);
        glUniform1i(m_uniforms["cellShadingLevels"],m_cell_shading_level);

}

void SpotLight::SetAsFlashLight(const Camera& camera) {
    m_transform = camera.getTransform();
    direction = camera.getDirection();
}

void SpotLight::SetupUniforms(std::map<std::string, GLint>& m_uniforms, GLuint shaderProgram) {
    m_uniforms["allowCellShading"] = glGetUniformLocation(shaderProgram, "allowCellShading");

    m_uniforms["cellShadingLevels"] = glGetUniformLocation(shaderProgram, "cellShadingLevels");

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

	m_uniforms["spotLight.base.range"] = glGetUniformLocation(shaderProgram, "spotLight.base.range");

}