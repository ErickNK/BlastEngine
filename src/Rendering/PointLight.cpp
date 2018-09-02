//
// Created by erick on 8/24/18.
//

#include "PointLight.h"

PointLight::PointLight() :
    Light(), position(glm::vec3(5.0f,0.0f,0.0f)),
    constant(1.0f),linear(0.045f),quadratic(0.0075f){}

PointLight::PointLight(int id, glm::vec3 color, glm::vec3 position,
                       GLfloat ambientIntensity, GLfloat diffuseIntensity,
                       GLfloat constant, GLfloat linear, GLfloat quadratic,
						GLfloat shadowWidth, GLfloat shadowHeight) :
    Light(color,ambientIntensity,diffuseIntensity,shadowWidth,shadowHeight), id(id), position(position),
    constant(constant),linear(linear),quadratic(quadratic){}


void PointLight::UseLight(PointLightUniforms *pointLightUniforms, int shadowTextureUnit) {

	//Start using Lights shadow map
	shadowMap->UseShadowMap(shadowTextureUnit);

	//Set shadowTextureUnit
	glUniform1i(pointLightUniforms[id].shadow_map_u, shadowTextureUnit);

    glUniform3f(pointLightUniforms[id].position_u,position.x,position.y,position.z);

    glUniform1f(pointLightUniforms[id].attenuation_constant_u,constant);

    glUniform1f(pointLightUniforms[id].attenuation_linear_u,linear);

    glUniform1f(pointLightUniforms[id].attenuation_quadratic_u,quadratic);

    glUniform3f(pointLightUniforms[id].base.color_u,color.x,color.y,color.z);

    glUniform1f(pointLightUniforms[id].base.ambient_intensity_u,ambientIntensity);

    glUniform1f(pointLightUniforms[id].base.diffuse_intensity_u,diffuseIntensity);
}

PointLight::~PointLight() = default;

void PointLight::SetupUniforms(PointLightUniforms *pointLightUniforms, GLuint shaderProgram) {
	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++) {

		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].shadowMap", i);
		pointLightUniforms[i].shadow_map_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.colour", i);
		pointLightUniforms[i].base.color_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
		pointLightUniforms[i].base.ambient_intensity_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
		pointLightUniforms[i].base.diffuse_intensity_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		pointLightUniforms[i].position_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].attenuationConstant", i);
		pointLightUniforms[i].attenuation_constant_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].attenuationLinear", i);
		pointLightUniforms[i].attenuation_linear_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].attenuationQuadratic", i);
		pointLightUniforms[i].attenuation_quadratic_u = glGetUniformLocation(shaderProgram, locBuff);
	}
}


