//
// Created by erick on 10/10/18.
//

#ifndef BLASTENGINE_DIFFEREDSHADER_H
#define BLASTENGINE_DIFFEREDSHADER_H


#include "Shader.h"
#include "../Material.h"
#include "../Lighting/DirectionalLight.h"
#include "../Lighting/PointLight.h"
#include "../Lighting/SpotLight.h"
#include "../RenderingEngine.h"

class DifferedGeometryPassShader : public Shader{
public:
    DifferedGeometryPassShader() : Shader(DIFFERED_GEOMETRYPASS_RENDERING_SHADER){
        m_shaderFiles[GL_VERTEX_SHADER] = "DifferedGeometryPass.vert";
        m_shaderFiles[GL_FRAGMENT_SHADER] = "DifferedGeometryPass.frag";
    }

    void CreateUniforms() override {
        Shader::CreateUniforms();
        Material::SetupUniforms(m_uniforms,m_program);
    }
};

class DifferedLightPassShader : public Shader{
public:
    DifferedLightPassShader() : Shader(DIFFERED_LIGHTPASS_RENDERING_SHADER){
        m_shaderFiles[GL_VERTEX_SHADER] = "DifferedLightPass.vert";
        m_shaderFiles[GL_FRAGMENT_SHADER] = "DifferedLightPass.frag";
    }

    void CreateUniforms() override {
        Shader::CreateUniforms();
        DirectionalLight::SetupUniforms(m_uniforms,m_program);
        PointLight::SetupUniforms(m_uniforms,m_program);
        SpotLight::SetupUniforms(m_uniforms,m_program);
        m_uniforms["positionTexture"] = glGetUniformLocation(m_program, "positionTexture");
        m_uniforms["normalTexture"] = glGetUniformLocation(m_program, "normalTexture");
        m_uniforms["diffuseTexture"] = glGetUniformLocation(m_program, "diffuseTexture");
        m_uniforms["specularTexture"] = glGetUniformLocation(m_program, "specularTexture");
        m_uniforms["materialTexture"] = glGetUniformLocation(m_program, "materialTexture");
    }

    void SetEngine(RenderingEngine* engine){
        //Set counts
        Uniform1i("directionalLightCount",engine->getCurrentScene()->getDirectionalLightsCount());
        Uniform1i("pointLightCount",engine->getCurrentScene()->getPointLightsCount());
        Uniform1i("spotLightCount",engine->getCurrentScene()->getSpotLightsCount());

        //Set lights
        for(LightEntity* lightEntity: engine->getCurrentScene()->getLights()){
            lightEntity->UseLight(this);
        }
    }
};


#endif //BLASTENGINE_DIFFEREDSHADER_H
