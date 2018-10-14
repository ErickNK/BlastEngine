//
// Created by erick on 9/9/18.
//

#include "ForwardSpotLightShader.h"
#include "Shader.h"
#include "../Material.h"

ForwardSpotLightShader::ForwardSpotLightShader() : Shader(FORWARD_SPOT_LIGHT_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "BasicShader.vert";
    m_shaderFiles[GL_FRAGMENT_SHADER] = "ForwardSpotLight.frag";
}

void ForwardSpotLightShader::CreateUniforms() {
    Shader::CreateUniforms();
    Material::SetupUniforms(m_uniforms,m_program);
    SpotLight::SetupUniforms(m_uniforms,m_program);
}

void ForwardSpotLightShader::setLight(SpotLight * sLight) {
    sLight->UseLight(this);
}