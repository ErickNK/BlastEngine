//
// Created by erick on 9/22/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_WATERSHADER_H
#define MORDEROPENGLUDEMYTUTORIAL_WATERSHADER_H


#include "../../Common/CommonValues.h"
#include "Shader.h"
#include "../Primitives/Water.h"
#include "../../Core/Entities/LightEntity.h"

class WaterShader: public Shader  {
public:
    WaterShader() : Shader(WATER_SHADER){
        m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/WaterShader.vert";
        m_shaderFiles[GL_FRAGMENT_SHADER] = "../res/shaders/WaterShader.frag";
    }

    void CreateUniforms() override {
        Shader::CreateUniforms();
        m_uniforms["material.reflectionTexture"] = glGetUniformLocation(m_program, "material.reflectionTexture");
        m_uniforms["material.refractionTexture"] = glGetUniformLocation(m_program, "material.refractionTexture");
        m_uniforms["material.refractionDepthTexture"] = glGetUniformLocation(m_program, "material.refractionDepthTexture");
        m_uniforms["material.dudvMap"] = glGetUniformLocation(m_program, "material.dudvMap");
        m_uniforms["material.normalMap"] = glGetUniformLocation(m_program, "material.normalMap");
        m_uniforms["material.fresnelIntensity"] = glGetUniformLocation(m_program, "material.fresnelIntensity");
        m_uniforms["moveFactor"] = glGetUniformLocation(m_program, "moveFactor");
        m_uniforms["waveStrength"] = glGetUniformLocation(m_program, "waveStrength");
        m_uniforms["waveTiling"] = glGetUniformLocation(m_program, "waveTiling");
        m_uniforms["lightColor"] = glGetUniformLocation(m_program, "lightColor");
        m_uniforms["lightDirection"] = glGetUniformLocation(m_program, "lightDirection");
    }

    void SetWater(Water* water){
        Uniform1f("waveTiling",water->wave_tiling);
        Uniform1f("waveStrength",water->wave_strength);
        Uniform1f("moveFactor",water->moveFactor);
    }

    void SetLights(const std::vector<LightEntity *> &vector) {
        Uniform4f("lightColor",1,1,1,1);
        Uniform3f("lightDirection",0,-1,-1);
//        glm::vec4 totalLight;
//        for (LightEntity *const & light: vector){
//            totalLight += light->
//        }
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_WATERSHADER_H
