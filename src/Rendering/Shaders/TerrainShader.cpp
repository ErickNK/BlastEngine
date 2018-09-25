//
// Created by erick on 9/9/18.
//

#include "TerrainShader.h"

TerrainShader::TerrainShader() : Shader(TERRAIN_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/SimpleTerrainShader.vert";
    m_shaderFiles[GL_FRAGMENT_SHADER] = "../res/shaders/SimpleTerrainShader.frag";
}

void TerrainShader::CreateUniforms() {
    Shader::CreateUniforms();
    m_uniforms["backgroundTexture"] = glGetUniformLocation(m_program, "backgroundTexture");
    m_uniforms["rTexture"] = glGetUniformLocation(m_program, "rTexture");
    m_uniforms["bTexture"] = glGetUniformLocation(m_program, "bTexture");
    m_uniforms["gTexture"] = glGetUniformLocation(m_program, "gTexture");
    m_uniforms["blendMap"] = glGetUniformLocation(m_program, "blendMap");
}

//TODO: move material stuff to material class
void TerrainShader::setTerrain(Terrain * terrain) {
    glUniform1i(m_uniforms["backgroundTexture"], 0);
    glUniform1i(m_uniforms["rTexture"], 0);
    glUniform1i(m_uniforms["gTexture"], 0);
    glUniform1i(m_uniforms["bTexture"], 0);
    glUniform1i(m_uniforms["blendMap"], 0);

    for (auto &i : terrain->getMaterial()->getTextures()) {
        auto textureUnit = static_cast<unsigned int>(getAvailableDrawingTextureUnit());
        TextureTypeEnum type = i->GetTextureType();

        if (type == R_TEXTURE) {
            glUniform1i(m_uniforms["rTexture"], textureUnit);
        }else if (type == G_TEXTURE) {
            glUniform1i(m_uniforms["gTexture"], textureUnit);
        }else if(type == B_TEXTURE){
            glUniform1i(m_uniforms["bTexture"], textureUnit);
        }else if(type == BACKGROUND_TEXTURE){
            glUniform1i(m_uniforms["backgroundTexture"], textureUnit);
        }else if(type == BLEND_MAP_TEXTURE){
            glUniform1i(m_uniforms["blendMap"], textureUnit);
        }

        i->Bind(textureUnit);
    }
}
