//
// Created by erick on 9/7/18.
//

#include "DirectionalLightShadowMapShader.h"

DirectionalLightShadowMapShader::DirectionalLightShadowMapShader() : Shader(DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/DirectionalLightShadowMapShader.vert";
    m_shaderFiles[GL_FRAGMENT_SHADER] = "../res/shaders/DirectionalLightShadowMapShader.frag";
}

void DirectionalLightShadowMapShader::CreateUniforms() {
    Shader::CreateUniforms();
    DirectionalLight::SetupUniforms(m_uniforms,m_program);
}