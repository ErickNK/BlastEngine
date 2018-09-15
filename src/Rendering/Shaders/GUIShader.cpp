//
// Created by erick on 9/15/18.
//

#include "GUIShader.h"
GUIShader::GUIShader() : Shader(TERRAIN_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/GUIShader.vert";
    m_shaderFiles[GL_FRAGMENT_SHADER] = "../res/shaders/GUIShader.frag";
}

void GUIShader::CreateUniforms() {
    Shader::CreateUniforms();
    m_uniforms["gui_texture"] = glGetUniformLocation(m_program, "gui_texture");
}