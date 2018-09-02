//
// Created by erick on 8/25/18.
//

#include "SpotLight.h"


SpotLight::SpotLight():
    PointLight(),
    direction(glm::vec3(0.0f,-1.0f, 0.0f)),
    edge(0.0f),  procEdge(cosf(glm::radians(edge))){}

SpotLight::SpotLight(
        int id, glm::vec3 color, glm::vec3 position, glm::vec3 direction,
        GLfloat ambientIntensity, GLfloat diffuseIntensity,
        GLfloat constant, GLfloat linear, GLfloat quadratic,
        GLfloat edge, GLfloat shadowWidth, GLfloat shadowHeight) :
        PointLight(
                id, color, position,
                ambientIntensity, diffuseIntensity,
                constant, linear, quadratic,
				shadowWidth,shadowHeight
                ),
        direction(glm::normalize(direction)), edge(edge), procEdge(cosf(glm::radians(edge))){}

SpotLight::~SpotLight() {}

void SpotLight::UseLight(SpotLightUniforms *spotLightUniforms, int shadowTextureUnit) {

		//Start using Lights shadow map
		shadowMap->UseShadowMap(shadowTextureUnit);

		//Set shadowTextureUnit
		glUniform1i(spotLightUniforms[id].shadow_map_u, shadowTextureUnit);

        glUniform3f(spotLightUniforms[id].position_u,position.x,position.y,position.z);

        glUniform3f(spotLightUniforms[id].direction_u,direction.x,position.y,position.z);

        glUniform1f(spotLightUniforms[id].edge_u,procEdge);

        glUniform1f(spotLightUniforms[id].attenuation_constant_u,constant);

        glUniform1f(spotLightUniforms[id].attenuation_linear_u,linear);

        glUniform1f(spotLightUniforms[id].attenuation_quadratic_u,quadratic);

        glUniform3f(spotLightUniforms[id].base.color_u,color.x,color.y,color.z);

        glUniform1f(spotLightUniforms[id].base.ambient_intensity_u,ambientIntensity);

        glUniform1f(spotLightUniforms[id].base.diffuse_intensity_u,diffuseIntensity);
}

void SpotLight::SetAsFlashLight(glm::vec3 pos, glm::vec3 dir) {
        position = pos;
        direction = dir;
}

void SpotLight::SetupUniforms(SpotLightUniforms *spotLightUniforms, GLuint shaderProgram) {
	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++) {

		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].shadowMap", i);
		spotLightUniforms[i].shadow_map_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.colour", i);
		spotLightUniforms[i].base.color_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.ambientIntensity", i);
		spotLightUniforms[i].base.ambient_intensity_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.base.diffuseIntensity", i);
		spotLightUniforms[i].base.diffuse_intensity_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
		spotLightUniforms[i].position_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
		spotLightUniforms[i].direction_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
		spotLightUniforms[i].edge_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.attenuationConstant", i);
		spotLightUniforms[i].attenuation_constant_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.attenuationLinear", i);
		spotLightUniforms[i].attenuation_linear_u = glGetUniformLocation(shaderProgram, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.attenuationQuadratic", i);
		spotLightUniforms[i].attenuation_quadratic_u = glGetUniformLocation(shaderProgram, locBuff);
	}
}
