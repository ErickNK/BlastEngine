//
// Created by erick on 9/8/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FORWARDDIRECTIONALLIGHTSHADER_H
#define MORDEROPENGLUDEMYTUTORIAL_FORWARDDIRECTIONALLIGHTSHADER_H


#include "Shader.h"

class DirectionalLight;

class ForwardDirectionalLightShader: public Shader {
public:
    ForwardDirectionalLightShader();

    void CreateUniforms() override;

    void setLight(DirectionalLight* dlight);

private:

};


#endif //MORDEROPENGLUDEMYTUTORIAL_FORWARDDIRECTIONALLIGHTSHADER_H
