//
// Created by erick on 9/20/18.
//

#include "AnimationShader.h"
AnimationShader::AnimationShader() : Shader(DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER){
    m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/DirectionalLightShadowMapShader.vert";
    m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/DirectionalLightShadowMapShader.vert";
}

void SetAnimated(AnimatedEntity *animatedEntity){

}

void AnimationShader::CreateUniforms() {
    Shader::CreateUniforms();

}