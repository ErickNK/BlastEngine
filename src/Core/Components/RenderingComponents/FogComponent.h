//
// Created by erick on 9/9/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_FOGCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_FOGCOMPONENT_H

#include "../../../Rendering/Shaders/FogShader.h"
#include "../../../Rendering/RenderingEngine.h"
#include "../EntityComponent.h"

class FogComponent : public EntityComponent<EffectEntity> {
public:

    FogComponent(): EntityComponent(FOG_COMPONENT) {}

    void Render(RenderingEngine *engine) const override {
        auto * shader = (FogShader*) engine->PushShader(FOG_SHADER);

            shader->SetFog(reinterpret_cast<Fog *>(m_entity));

            engine->RenderAllMeshed();

        engine->PopShader();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_FOGCOMPONENT_H
