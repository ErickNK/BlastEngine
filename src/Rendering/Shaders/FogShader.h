//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FOGSHADER_H
#define MORDEROPENGLUDEMYTUTORIAL_FOGSHADER_H

#include "Shader.h"

class Fog;

class FogShader: public Shader {

public:
    FogShader();

    void CreateUniforms() override;

    void SetFog(Fog * fog);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_FOGSHADER_H
