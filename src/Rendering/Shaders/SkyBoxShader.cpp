//
// Created by erick on 9/15/18.
//

#include "SkyBoxShader.h"
SkyBoxShader::SkyBoxShader() : Shader(TERRAIN_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/SkyBox.vert";
    m_shaderFiles[GL_FRAGMENT_SHADER] = "../res/shaders/SkyBox.frag";
}

