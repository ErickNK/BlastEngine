//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SHADOWRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_SHADOWRENDERERCOMPONENT_H


#include "../../../Rendering/RenderingEngine.h"
#include "LightComponent.h"

class ShadowRendererComponent : public LightComponent{

    void RenderDirectionalLight(RenderingEngine* engine) const override {
        auto * shader = (DirectionalLightShadowMapShader*) engine->BindShader(DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER);

            glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT);

            //Set view port same size as our shadow-map framebuffer
            glViewport(0, 0, m_entity->GetShadowMap()->GetShadowWidth(), m_entity->GetShadowMap()->GetShadowHeight());

            m_entity->GetShadowMap()->BindFrameBuffer(); //Begin writing

                shader->SetDirectionalLight(dynamic_cast<DirectionalLight *>(m_entity));

                engine->RenderAllMeshed();

            m_entity->GetShadowMap()->UnBindFrameBuffer(); //stop writing

        engine->UnBindShader(DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER);
    }

    virtual void RenderPointLight(RenderingEngine* engine) const {

    }

    virtual void RenderSpotLight(RenderingEngine* engine) const {

    }

};


#endif //MORDEROPENGLUDEMYTUTORIAL_SHADOWRENDERERCOMPONENT_H
