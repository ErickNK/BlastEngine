//
// Created by erick on 9/9/18.
//

#include "TerrainShader.h"

TerrainShader::TerrainShader() : Shader(TERRAIN_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "DifferedTerrainShader.vert";
    m_shaderFiles[GL_FRAGMENT_SHADER] = "DifferedTerrainShader.frag";
}

void TerrainShader::CreateUniforms() {
    Shader::CreateUniforms();
    Material::SetupUniforms(m_uniforms,m_program);
    m_uniforms["backgroundTexture"] = glGetUniformLocation(m_program, "backgroundTexture");
    m_uniforms["rTexture"] = glGetUniformLocation(m_program, "rTexture");
    m_uniforms["bTexture"] = glGetUniformLocation(m_program, "bTexture");
    m_uniforms["gTexture"] = glGetUniformLocation(m_program, "gTexture");
    m_uniforms["blendMap"] = glGetUniformLocation(m_program, "blendMap");
}

