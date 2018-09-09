//
// Created by erick on 9/9/18.
//

#include "TerrainShader.h"

TerrainShader::TerrainShader() : Shader(FORWARD_POINT_LIGHT_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/TerrainShader.vert";
    m_shaderFiles[GL_FRAGMENT_SHADER] = "../res/shaders/TerrainShader.frag";
}

void TerrainShader::CreateUniforms() {
    Shader::CreateUniforms();
//    Terrain::SetupUniforms(m_uniforms,m_program);
}

void TerrainShader::setTerrain(Terrain * terrain) {
//    terrain->UseTerrain(m_uniforms,getAvailableGlobalTextureUnit());
}
