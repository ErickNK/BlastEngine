//
// Created by erick on 9/8/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FORWARDAMBIENTSHADER_H
#define MORDEROPENGLUDEMYTUTORIAL_FORWARDAMBIENTSHADER_H


#include "Shader.h"
#include "../Lighting/Light.h"

class ForwardAmbientShader : public Shader {
public:
    ForwardAmbientShader();

    void CreateUniforms() override;

    void setLight(Light* light);
    void setLight(glm::vec3 color,float ambientIntensity);

private:
};


#endif //MORDEROPENGLUDEMYTUTORIAL_FORWARDAMBIENTSHADER_H