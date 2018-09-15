//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SHADOWRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_SHADOWRENDERERCOMPONENT_H


#include "../../../Rendering/RenderingEngine.h"
#include "LightComponent.h"

class ShadowRendererComponent : public LightComponent{

    void RenderDirectionalLight(RenderingEngine* engine) const override {
        auto * shader = (DirectionalLightShadowMapShader*) engine->GetShader(DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER);

        engine->SetCurrentShader(DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER);

        shader->Bind();

            glClear(GL_DEPTH_BUFFER_BIT);

            //Set view port same size as our shadow-map framebuffer
            glViewport(0, 0, m_light->GetShadowMap()->GetShadowWidth(), m_light->GetShadowMap()->GetShadowHeight());

            m_light->GetShadowMap()->BindFrameBuffer(); //Begin writing

                shader->SetDirectionalLight(dynamic_cast<DirectionalLight *>(m_light));

                engine->RenderAllMeshed();

            m_light->GetShadowMap()->UnBindFrameBuffer(); //stop writing

        shader->UnBind();
    }

    virtual void RenderPointLight(RenderingEngine* engine) const {

    }

    virtual void RenderSpotLight(RenderingEngine* engine) const {

    }

};


#endif //MORDEROPENGLUDEMYTUTORIAL_SHADOWRENDERERCOMPONENT_H
