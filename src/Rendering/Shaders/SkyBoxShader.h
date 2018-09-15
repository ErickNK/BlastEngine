//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SKYBOXSHADER_H
#define MORDEROPENGLUDEMYTUTORIAL_SKYBOXSHADER_H


#include "Shader.h"
#include "../SkyBox.h"

class SkyBoxShader: public Shader {
public:
    SkyBoxShader();

    void CreateUniforms() override;

    void SetSkyBox(SkyBox * skyBox);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_SKYBOXSHADER_H
