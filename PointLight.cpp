//
// Created by erick on 8/24/18.
//

#include "PointLight.h"

PointLight::PointLight() :
    Light(), position(glm::vec3(5.0f,0.0f,0.0f)),
    constant(1.0f),linear(0.045f),quadratic(0.0075f){}

PointLight::PointLight(int id, glm::vec3 color, glm::vec3 position,
                       GLfloat ambientIntensity, GLfloat diffuseIntensity,
                       GLfloat constant, GLfloat linear, GLfloat quadratic) :
    Light(color,ambientIntensity,diffuseIntensity), id(id), position(position),
    constant(constant),linear(linear),quadratic(quadratic){}


void PointLight::UseLight(PointLightUniforms *pointLightUniforms) {

    glUniform3f(pointLightUniforms[id].position_u,position.x,position.y,position.z);

    glUniform1f(pointLightUniforms[id].attenuation_constant_u,constant);

    glUniform1f(pointLightUniforms[id].attenuation_linear_u,linear);

    glUniform1f(pointLightUniforms[id].attenuation_quadratic_u,quadratic);

    glUniform3f(pointLightUniforms[id].base.color_u,color.x,color.y,color.z);

    glUniform1f(pointLightUniforms[id].base.ambient_intensity_u,ambientIntensity);

    glUniform1f(pointLightUniforms[id].base.diffuse_intensity_u,diffuseIntensity);
}

PointLight::~PointLight() = default;


