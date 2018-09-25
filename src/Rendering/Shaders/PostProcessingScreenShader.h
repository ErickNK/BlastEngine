//
// Created by erick on 9/21/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_POSTPROCESSINGSCREENSHADER_H
#define MORDEROPENGLUDEMYTUTORIAL_POSTPROCESSINGSCREENSHADER_H

#include "../../Common/CommonValues.h"
#include "Shader.h"

class PostProcessingScreenShader: public Shader {
public:
    PostProcessingScreenShader() : Shader(POST_PROCESSING_SCREEN_SHADER){
        m_shaderFiles[GL_VERTEX_SHADER] = "../res/shaders/PostProcessingScreen.vert";
        m_shaderFiles[GL_FRAGMENT_SHADER] = "../res/shaders/PostProcessingScreen.frag";
    }

    void CreateUniforms() override {
        Shader::CreateUniforms();
        m_uniforms["texture"] = glGetUniformLocation(m_program, "texture");
    }

};


#endif //MORDEROPENGLUDEMYTUTORIAL_POSTPROCESSINGSCREENSHADER_H
