//
// Created by erick on 9/7/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_DIRECTIONALLIGHTSHADOWMAPSHADER_H
#define MORDEROPENGLUDEMYTUTORIAL_DIRECTIONALLIGHTSHADOWMAPSHADER_H


#include "Shader.h"
#include "../Lighting/DirectionalLight.h"

class DirectionalLightShadowMapShader : public Shader{
public:
    DirectionalLightShadowMapShader();

    void SetDirectionalLight(DirectionalLight *dLight);

    void CreateUniforms() override;

private:
};


#endif //MORDEROPENGLUDEMYTUTORIAL_DIRECTIONALLIGHTSHADOWMAPSHADER_H
