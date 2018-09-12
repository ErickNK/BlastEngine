//
// Created by erick on 9/9/18.
//

#include "FogShader.h"
#include "../Fog.h"


FogShader::FogShader() : Shader(FOG_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/FogShader.vert";
    m_shaderFiles[GL_FRAGMENT_SHADER] = "../res/shaders/FogShader.frag";
}

void FogShader::CreateUniforms() {
    Shader::CreateUniforms();
    m_uniforms["fogDensity"] = glGetUniformLocation(m_program, "fogDensity");
    m_uniforms["fogGradient"] = glGetUniformLocation(m_program, "fogGradient");
    m_uniforms["fogColor"] = glGetUniformLocation(m_program, "fogColor");
}

void FogShader::SetFog(Fog* fog) {
    glUniform4f(m_uniforms["fogColor"],fog->m_color.x,fog->m_color.y,fog->m_color.z,fog->m_color.w);
    glUniform1f(m_uniforms["fogDensity"],fog->m_fogDensity);
    glUniform1f(m_uniforms["fogGradient"],fog->m_fogGradient);
}

