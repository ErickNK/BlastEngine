//
// Created by erick on 8/24/18.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() :
    Light(),
    direction(glm::vec3(0.0f,-1.0f,0.0f)) 
{
	lightProjection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 20.0f);
}

DirectionalLight::DirectionalLight(glm::vec3 color,glm::vec3 direction,GLfloat ambientIntensity, GLfloat diffuseIntensity,
	GLfloat shadowWidth, GLfloat shadowHeight) :
    Light(color,ambientIntensity,diffuseIntensity,shadowWidth,shadowHeight),
    direction(glm::normalize(direction))
{
	lightProjection = glm::ortho(-5.0f,5.0f,-5.0f,5.0f,0.1f,20.0f);
}

DirectionalLight::~DirectionalLight() = default;
	
void DirectionalLight::UseLight(DirectionalLightUniforms *directionalLightUniforms,int shadowTextureUnit) {

	//Start using Lights shadow map
	shadowMap->UseShadowMap(shadowTextureUnit);

	//Set shadowTextureUnit
	glUniform1i(directionalLightUniforms->shadow_map_u, shadowTextureUnit);

	//Set Light Space
	glUniformMatrix4fv(directionalLightUniforms->light_space_u, 1, GL_FALSE, glm::value_ptr(lightSpace));

    //Set Light Direction
    glUniform3f(directionalLightUniforms->direction_u,direction.x,direction.y,direction.z);

    //Set Light Color
    glUniform3f(directionalLightUniforms->base.color_u,color.x,color.y,color.z);

    //Set Ambient Intensity
    glUniform1f(directionalLightUniforms->base.ambient_intensity_u,ambientIntensity);

    //Set Diffuse Intensity
    glUniform1f(directionalLightUniforms->base.diffuse_intensity_u,diffuseIntensity);
}


void DirectionalLight::SetupLightSpace(DirectionalLightUniforms *directionalLightUniforms, GLuint shaderProgram) {
	//Calculate Light space
	lightSpace = lightProjection * glm::lookAt(-direction,glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));

	//Set Light Space
	directionalLightUniforms->light_space_u = glGetUniformLocation(shaderProgram, "directionalLightSpace");
	glUniformMatrix4fv(directionalLightUniforms->light_space_u, 1, GL_FALSE, glm::value_ptr(lightSpace));
}


void DirectionalLight::SetupUniforms(DirectionalLightUniforms *directionalLightUniforms,GLuint shaderProgram) {

	directionalLightUniforms->light_space_u =
			glGetUniformLocation(shaderProgram, "directionalLightSpace");

	directionalLightUniforms->shadow_map_u =
			glGetUniformLocation(shaderProgram, "directionalLight.shadowMap");

    directionalLightUniforms->direction_u =
            glGetUniformLocation(shaderProgram, "directionalLight.direction");

    directionalLightUniforms->base.color_u =
            glGetUniformLocation(shaderProgram, "directionalLight.base.colour");

    directionalLightUniforms->base.ambient_intensity_u =
            glGetUniformLocation(shaderProgram, "directionalLight.base.ambientIntensity");

    directionalLightUniforms->base.diffuse_intensity_u =
            glGetUniformLocation(shaderProgram, "directionalLight.base.diffuseIntensity");
}
