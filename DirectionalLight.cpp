//
// Created by erick on 8/24/18.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() :
    Light(),
    direction(glm::vec3(0.0f,-1.0f,0.0f)) {}

DirectionalLight::DirectionalLight(glm::vec3 color,glm::vec3 direction,GLfloat ambientIntensity, GLfloat diffuseIntensity) :
    Light(color,ambientIntensity,diffuseIntensity),
    direction(direction){}

DirectionalLight::~DirectionalLight() = default;

void DirectionalLight::UseLight(DirectionalLightUniforms *directionalLightUniforms) {
    //Set Light Direction
    glUniform3f(directionalLightUniforms->direction_u,direction.x,direction.y,direction.z);

    //Set Light Color
    glUniform3f(directionalLightUniforms->base.color_u,color.x,color.y,color.z);

    //Set Ambient Intensity
    glUniform1f(directionalLightUniforms->base.ambient_intensity_u,ambientIntensity);

    //Set Diffuse Intensity
    glUniform1f(directionalLightUniforms->base.diffuse_intensity_u,diffuseIntensity);
}


void DirectionalLight::SetupUniforms(DirectionalLightUniforms *directionalLightUniforms,GLuint shaderProgram) {
    directionalLightUniforms->direction_u =
            glGetUniformLocation(shaderProgram, "directionalLight.direction");

    directionalLightUniforms->base.color_u =
            glGetUniformLocation(shaderProgram, "directionalLight.base.colour");

    directionalLightUniforms->base.ambient_intensity_u =
            glGetUniformLocation(shaderProgram, "directionalLight.base.ambientIntensity");

    directionalLightUniforms->base.diffuse_intensity_u =
            glGetUniformLocation(shaderProgram, "directionalLight.base.diffuseIntensity");
}
