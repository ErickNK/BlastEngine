//
// Created by erick on 9/7/18.
//

#include "DirectionalLightShadowMapShader.h"

DirectionalLightShadowMapShader::DirectionalLightShadowMapShader() : Shader(DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/DirectionalLightShadowMapShader.vert";
}

void DirectionalLightShadowMapShader::SetDirectionalLight(DirectionalLight *dLight) {
    dLight->SetupLightSpace(m_uniforms, m_program);
}

void DirectionalLightShadowMapShader::CreateUniforms() {
    Shader::CreateUniforms();
    DirectionalLight::SetupUniforms(m_uniforms,m_program);
}