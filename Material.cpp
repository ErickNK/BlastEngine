//
// Created by erick on 8/24/18.
//

#include "Material.h"

Material::Material() :
    specularIntensity(0.0f),
    shininess(0.0f) {}

Material::Material(GLfloat specularIntensity, GLfloat shininess) :
    specularIntensity(specularIntensity),
    shininess(shininess) {}

Material::~Material() {}

void Material::UseMaterial(MaterialUniforms *materialUniforms) {
    //Set Specular Intensity
    glUniform1f(materialUniforms->specular_intensity_u,specularIntensity);

    //Set Shininess
    glUniform1f(materialUniforms->shininess_u,shininess);
}

void Material::SetupUniforms(MaterialUniforms *materialUniforms,GLuint shaderProgram) {
    //Create Shininess Uniform
    materialUniforms->shininess_u = glGetUniformLocation(shaderProgram, "material.shininess");

    //Create Specular Intensity Uniform
    materialUniforms->specular_intensity_u = glGetUniformLocation(shaderProgram, "material.specularIntensity");
}
