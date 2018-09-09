//
// Created by erick on 9/9/18.
//

#include "ForwardPointLightShader.h"
#include "../Material.h"

ForwardPointLightShader::ForwardPointLightShader() : Shader(FORWARD_POINT_LIGHT_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/BasicShader.vert";
    m_shaderFiles[GL_FRAGMENT_SHADER] = "../res/shaders/ForwardPointLight.frag";
}

void ForwardPointLightShader::CreateUniforms() {
    Shader::CreateUniforms();
    Material::SetupUniforms(m_uniforms,m_program);
    PointLight::SetupUniforms(m_uniforms,m_program);
}

void ForwardPointLightShader::setLight(PointLight * pLight) {
    pLight->UseLight(m_uniforms,getAvailableGlobalTextureUnit());
}
