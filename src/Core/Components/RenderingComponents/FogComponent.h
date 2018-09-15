//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FOGCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_FOGCOMPONENT_H

#include "../../../Rendering/Shaders/FogShader.h"
#include "../../../Rendering/RenderingEngine.h"
#include "../EntityComponent.h"

class FogComponent : public EntityComponent<EffectEntity,RenderingEngine> {

    void Render(RenderingEngine *engine) const override {
        auto * shader = (FogShader*) engine->GetShader(FOG_SHADER);

        engine->SetCurrentShader(FOG_SHADER);

        shader->Bind();

            shader->SetFog(reinterpret_cast<Fog *>(m_entity));

            engine->RenderAllMeshed();

        shader->UnBind();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_FOGCOMPONENT_H
