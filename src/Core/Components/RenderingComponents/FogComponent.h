//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FOGCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_FOGCOMPONENT_H

#include "../EffectComponent.h"
#include "../../../Rendering/Shaders/FogShader.h"
#include "../../../Rendering/RenderingEngine.h"

class FogComponent : public EffectComponent {

    void RenderEffect(RenderingEngine* engine) const override {
        auto * shader = (FogShader*) engine->GetShader(FOG_SHADER);

        engine->SetCurrentShader(FOG_SHADER);

        shader->Bind();

            shader->SetFog((Fog *)(m_parent));

            engine->RenderAllMeshed();

        shader->UnBind();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_FOGCOMPONENT_H
