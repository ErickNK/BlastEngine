//
// Created by erick on 9/20/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ANIMATIONSHADER_H
#define MORDEROPENGLUDEMYTUTORIAL_ANIMATIONSHADER_H


#include "Shader.h"
#include "../../Animation/AnimatedEntity.h"

class AnimationShader : public Shader {
public:
    AnimationShader();

    void SetAnimated(AnimatedEntity *animatedEntity);

    void CreateUniforms() override;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_ANIMATIONSHADER_H
