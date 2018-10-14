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

void SpotLight::UseLight(Shader* shader) {

		//Start using Lights shadow map
        auto shadowTextureUnit = static_cast<GLuint>(shader->getAvailableGlobalTextureUnit());
        m_shadow.shadow_map_fbo.UseTexture(m_shadow.shadow_map_texture,shadowTextureUnit);

        char locBuff[100] = {'\0'};

		//Set shadowTextureUnit
        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].shadowMap",m_id);
        shader->Uniform1i(locBuff, shadowTextureUnit);

        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].base.position",m_id);
        shader->Uniform3f(locBuff,m_transform.GetPos().x,m_transform.GetPos().y,m_transform.GetPos().z);

        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].dir",m_id);
        shader->Uniform3f(locBuff,direction.x,direction.y,direction.z);

        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].edge",m_id);
        shader->Uniform1f(locBuff,procEdge);

        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].base.attenuationConstant",m_id);
        shader->Uniform1f(locBuff,m_attenuation.z);

        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].base.attenuationLinear",m_id);
        shader->Uniform1f(locBuff,m_attenuation.y);

        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].base.attenuationQuadratic",m_id);
        shader->Uniform1f(locBuff,m_attenuation.x);

        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].base.base.colour",m_id);
        shader->Uniform3f(locBuff,color.x,color.y,color.z);

        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].base.base.ambientIntensity",m_id);
        shader->Uniform1f(locBuff,ambientIntensity);

        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].base.base.diffuseIntensity",m_id);
        shader->Uniform1f(locBuff ,diffuseIntensity);

        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].base.range",m_id);
        shader->Uniform1f(locBuff,m_range);

        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].base.base.allowCellShading",m_id);
        shader->Uniform1i(locBuff,m_allow_cell_shading);

        snprintf(locBuff, sizeof(locBuff), "spotLight[%d].base.base.cellShadingLevels",m_id);
        shader->Uniform1i(locBuff,m_cell_shading_level);

}

void SpotLight::SetAsFlashLight(const Camera& camera) {
    m_transform = camera.getTransform();
    direction = camera.getDirection();
}

void SpotLight::SetupUniforms(std::map<std::string, GLint>& m_uniforms, GLuint shaderProgram) {

    m_uniforms["spotLightCount"] = glGetUniformLocation(shaderProgram, "spotLightCount");

    m_uniforms["spotLight.base.base.allowCellShading"] = glGetUniformLocation(shaderProgram, "spotLight.base.base.allowCellShading");

    m_uniforms["spotLight.base.base.cellShadingLevels"] = glGetUniformLocation(shaderProgram, "spotLight.base.base.cellShadingLevels");

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