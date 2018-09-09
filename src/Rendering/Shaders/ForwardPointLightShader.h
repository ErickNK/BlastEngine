//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FORWARDPOINTLIGHTSHADER_H
#define MORDEROPENGLUDEMYTUTORIAL_FORWARDPOINTLIGHTSHADER_H


#include "Shader.h"
#include "../Lighting/PointLight.h"

class ForwardPointLightShader : public Shader{
public:
    ForwardPointLightShader();

    void CreateUniforms() override;

    void setLight(PointLight* plight);

};


#endif //MORDEROPENGLUDEMYTUTORIAL_FORWARDPOINTLIGHTSHADER_H
