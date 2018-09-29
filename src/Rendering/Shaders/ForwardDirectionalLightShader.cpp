//
// Created by erick on 9/8/18.
//

#include "ForwardDirectionalLightShader.h"
#include "../Material.h"
#include "../Lighting/DirectionalLight.h"

ForwardDirectionalLightShader::ForwardDirectionalLightShader() : Shader(FORWARD_DIRECTIONAL_LIGHT_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "BasicShader.vert";
    m_shaderFiles[GL_FRAGMENT_SHADER] = "ForwardDirectionalLight.frag";
}

void ForwardDirectionalLightShader::CreateUniforms() {
    Shader::CreateUniforms();
    Material::SetupUniforms(m_uniforms,m_program);
    DirectionalLight::SetupUniforms(m_uniforms,m_program);
}

void ForwardDirectionalLightShader::setLight(DirectionalLight * dLight) {
    dLight->UseLight(m_uniforms,getAvailableGlobalTextureUnit());
}
