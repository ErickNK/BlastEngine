//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FORWARDSPOTLIGHTSHADER_H
#define MORDEROPENGLUDEMYTUTORIAL_FORWARDSPOTLIGHTSHADER_H


#include "../Lighting/SpotLight.h"
#include "Shader.h"

class ForwardSpotLightShader: public Shader {
public:
    ForwardSpotLightShader();

    void CreateUniforms() override;

    void setLight(SpotLight* plight);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_FORWARDSPOTLIGHTSHADER_H
