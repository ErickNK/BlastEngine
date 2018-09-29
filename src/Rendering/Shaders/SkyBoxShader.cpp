//
// Created by erick on 9/15/18.
//

#include "SkyBoxShader.h"
#include "../Fog.h"
SkyBoxShader::SkyBoxShader() : Shader(SKY_BOX_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "SkyBox.vert";
    m_shaderFiles[GL_FRAGMENT_SHADER] = "SkyBox.frag";
}

void SkyBoxShader::CreateUniforms() {
    Shader::CreateUniforms();
    m_uniforms["fogColor"] = glGetUniformLocation(m_program,"fogColor");
    m_uniforms["fogLowerLimit"] = glGetUniformLocation(m_program,"fogLowerLimit");
    m_uniforms["fogUpperLimit"] = glGetUniformLocation(m_program,"fogUpperLimit");

    m_uniforms["skybox1"] = glGetUniformLocation(m_program,"skybox1");
    m_uniforms["skybox2"] = glGetUniformLocation(m_program,"skybox2");
    m_uniforms["blendFactor"] = glGetUniformLocation(m_program,"blendFactor");
}

void SkyBoxShader::SetSkyBox(SkyBox *skyBox) {
    if(skyBox->getFog() != nullptr){
        glUniform4f(m_uniforms["fogColor"], skyBox->getFog()->m_color.x,skyBox->getFog()->m_color.y,skyBox->getFog()->m_color.z,skyBox->getFog()->m_color.w);
        glUniform1f(m_uniforms["fogLowerLimit"], skyBox->getFogLowerLimit());
        glUniform1f(m_uniforms["fogUpperLimit"], skyBox->getFogUpperLimit());
    }

    glUniform1i(m_uniforms["skybox1"], 0);
    glUniform1i(m_uniforms["skybox2"], 1);
    glUniform1f(m_uniforms["blendFactor"], skyBox->getBlendFactor());
}


