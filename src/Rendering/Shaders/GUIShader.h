//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GUISHADER_H
#define MORDEROPENGLUDEMYTUTORIAL_GUISHADER_H


#include "../../Core/Entities/GUIEntity.h"

class GUIShader: public Shader {
public:
    GUIShader();

    void CreateUniforms() override;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GUISHADER_H
