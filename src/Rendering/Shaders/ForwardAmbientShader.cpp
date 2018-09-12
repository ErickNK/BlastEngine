//
// Created by erick on 9/8/18.
//

#include "ForwardAmbientShader.h"
#include "../Material.h"
#include "../Lighting/Light.h"

ForwardAmbientShader::ForwardAmbientShader() : Shader(FORWARD_AMBIENT_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/BasicShader.vert";
    m_shaderFiles[GL_FRAGMENT_SHADER] = "../res/shaders/ForwardAmbient.frag";
}

void ForwardAmbientShader::CreateUniforms() {
    Shader::CreateUniforms();
    m_uniforms["light.colour"] = glGetUniformLocation(m_program, "light.colour");
    m_uniforms["light.ambientIntensity"] = glGetUniformLocation(m_program, "light.ambientIntensity");
    Material::SetupUniforms(m_uniforms,m_program);
}

void ForwardAmbientShader::setLight(Light * light) {

    //Set Ambient Intensity
    glUniform3f(m_uniforms["light.colour"],light->getColor().x,light->getColor().y,light->getColor().z);
    glUniform1f(m_uniforms["light.ambientIntensity"],light->getAmbientIntensity());
}

void ForwardAmbientShader::setLight(glm::vec3 color,float ambientIntensity) {

    //Set Ambient Intensity
    glUniform3f(m_uniforms["light.colour"],color.x,color.y,color.z);
    glUniform1f(m_uniforms["light.ambientIntensity"], ambientIntensity);
}

