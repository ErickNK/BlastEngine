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



void Material::UseMaterial(Shader * shader) {
    //Set Specular Intensity
    glUniform1f(shader->getUniforms()[SPECULAR_INTENSITY_U],specularIntensity);

    //Set Shininess
    glUniform1f(shader->getUniforms()[SPECULAR_SHININESS_U],shininess);
}

void Material::SetupUniforms(Shader * shader) {
    //Create Shininess Uniform
    shader->getUniforms()[SPECULAR_SHININESS_U] = glGetUniformLocation(shader->getShaderProgram(), "material.shininess");

    //Create Specular Intensity Uniform
    shader->getUniforms()[SPECULAR_INTENSITY_U] = glGetUniformLocation(shader->getShaderProgram(), "material.specularIntensity");
}
