//
// Created by erick on 8/24/18.
//

#include "PointLight.h"
#include "../../Core/CoreEngine.h"
#include <glm/gtx/component_wise.hpp>

PointLight::PointLight() :
    LightEntity(POINT_LIGHT),
    m_attenuation(0.0075f,0.045f,1.0f){}

PointLight::PointLight(glm::vec3 color, glm::vec3 position,
                       GLfloat ambientIntensity, GLfloat diffuseIntensity,
					   glm::vec3 attenuation,
						GLfloat shadowWidth, GLfloat shadowHeight) :
    LightEntity(POINT_LIGHT,color,ambientIntensity,diffuseIntensity,shadowWidth,shadowHeight),
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

void PointLight::UseLight(Shader* shader) {

	//Start using Lights shadow map
	auto shadowTextureUnit = static_cast<GLuint>(shader->getAvailableGlobalTextureUnit());
    m_shadow.shadow_map_fbo.UseTexture(m_shadow.shadow_map_texture,shadowTextureUnit);

    char locBuff[100] = {'\0'};

	//Set shadowTextureUnit
    snprintf(locBuff, sizeof(locBuff), "pointLight[%d].shadowMap",m_id);
	shader->Uniform1i(locBuff, shadowTextureUnit);

    snprintf(locBuff, sizeof(locBuff), "pointLight[%d].position",m_id);
    shader->Uniform3f("pointLight.position",m_transform.GetPos().x,m_transform.GetPos().y,m_transform.GetPos().z);

    snprintf(locBuff, sizeof(locBuff), "pointLight[%d].attenuationConstant",m_id);
    shader->Uniform1f(locBuff,m_attenuation.z);

    snprintf(locBuff, sizeof(locBuff), "pointLight[%d].attenuationLinear",m_id);
    shader->Uniform1f(locBuff,m_attenuation.y);

    snprintf(locBuff, sizeof(locBuff), "pointLight[%d].attenuationQuadratic",m_id);
    shader->Uniform1f(locBuff,m_attenuation.x);

    snprintf(locBuff, sizeof(locBuff), "pointLight[%d].base.colour",m_id);
    shader->Uniform3f(locBuff,color.x,color.y,color.z);

    snprintf(locBuff, sizeof(locBuff), "pointLight[%d].base.ambientIntensity",m_id);
    shader->Uniform1f(locBuff,ambientIntensity);

    snprintf(locBuff, sizeof(locBuff), "pointLight[%d].base.diffuseIntensity",m_id);
    shader->Uniform1f(locBuff,diffuseIntensity);

    snprintf(locBuff, sizeof(locBuff), "pointLight[%d].range",m_id);
	shader->Uniform1f(locBuff,m_range);

    snprintf(locBuff, sizeof(locBuff), "pointLight[%d].base.allowCellShading",m_id);
	shader->Uniform1i(locBuff,m_allow_cell_shading);

    snprintf(locBuff, sizeof(locBuff), "pointLight[%d].base.cellShadingLevels",m_id);
    shader->Uniform1i(locBuff,m_cell_shading_level);

}

PointLight::~PointLight() = default;

void PointLight::SetupUniforms(std::map<std::string, GLint>& m_uniforms, GLuint shaderProgram) {

	m_uniforms["pointLightCount"] = glGetUniformLocation(shaderProgram, "pointLightCount");

	m_uniforms["pointLight.base.cellShadingLevels"] = glGetUniformLocation(shaderProgram, "pointLight.base.cellShadingLevels");

	m_uniforms["pointLight.base.allowCellShading"] = glGetUniformLocation(shaderProgram, "pointLight.base.allowCellShading");

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
