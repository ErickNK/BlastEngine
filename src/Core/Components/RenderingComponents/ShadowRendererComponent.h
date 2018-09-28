//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SHADOWRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_SHADOWRENDERERCOMPONENT_H


#include "../../../Rendering/RenderingEngine.h"
#include "LightComponent.h"

class ShadowRendererComponent : public LightComponent{
public:
    void Update(double time, float delta) override {
        EntityComponent::Update(time, delta);

//        m_entity->GetShadow().m_shadow_camera.getTransform().GetRot() = m_entity->getTransform().GetTransformedRot();
//        m_entity->GetShadow().m_shadow_camera.getTransform().GetPos() = m_entity->getTransform().GetTransformedPos();
        m_entity->GetShadow().m_shadow_camera.UpdateViewWithoutTurn(m_entity->getTransform());
    }

    void RenderDirectionalLight(RenderingEngine* engine) const override {
        auto * shader = (DirectionalLightShadowMapShader*) engine->BindShader(DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER);

            m_entity->GetShadowMapFBO().BindFrameBuffer(); //Begin writing
            m_entity->GetShadowMapFBO().setForDrawing(false,0);

                glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//                m_entity->GetShadow().m_shadow_camera.setViewMatrix(engine->getCurrentScene()->getCurrentCamera()->getViewMatrix());

                shader->UpdateCamera(m_entity->GetShadow().m_shadow_camera);

                engine->RenderAllMeshed();

            m_entity->GetShadowMapFBO().UnBindFrameBuffer(engine->getWindow()->getBufferWidth(),engine->getWindow()->getBufferHeight()); //stop writing

        engine->UnBindShader(DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER);

        GLenum someError = glGetError();
        assert( someError == GL_NO_ERROR);
    }

    virtual void RenderPointLight(RenderingEngine* engine) const {

    }

    virtual void RenderSpotLight(RenderingEngine* engine) const {

    }

};


#endif //MORDEROPENGLUDEMYTUTORIAL_SHADOWRENDERERCOMPONENT_H
