//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SHADOWRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_SHADOWRENDERERCOMPONENT_H


#include "../../../Rendering/RenderingEngine.h"
#include "LightComponent.h"

class ShadowRendererComponent : public LightComponent{
public:
    ShadowRendererComponent() : LightComponent() {}

    void Update(double time, float delta) override {
        EntityComponent::Update(time, delta);

//        m_entity->GetShadow().m_shadow_camera.getTransform().GetRot() = m_entity->getTransform().GetTransformedRot();
//        m_entity->GetShadow().m_shadow_camera.getTransform().GetPos() = m_entity->getTransform().GetTransformedPos();
        m_entity->GetShadow().m_shadow_camera.UpdateViewWithoutTurn(m_entity->getTransform());
    }

    void RenderDirectionalLight(RenderingEngine* engine) const override {
        auto * shader = (DirectionalLightShadowMapShader*) engine->PushShader(DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER);

            engine->PushFBO(m_entity->GetShadowMapFBO()); //Begin writing

                std::vector<int> buffers { (int) m_entity->GetShadow().shadow_map_texture};
                m_entity->GetShadowMapFBO()->setForDrawing(true,buffers);

                if(m_entity->GetShadow().m_flipFaces) glCullFace(GL_FRONT);

                    m_entity->GetShadowMapFBO()->ClearFBO();

                    shader->UpdateCamera(m_entity->GetShadow().m_shadow_camera);

                    engine->RenderAllMeshed();

                if(m_entity->GetShadow().m_flipFaces) glCullFace(GL_BACK);

            engine->PopFBO();

        engine->PopShader();

        glCheckError();

    }

    virtual void RenderPointLight(RenderingEngine* engine) const {

    }

    virtual void RenderSpotLight(RenderingEngine* engine) const {

    }

};


#endif //MORDEROPENGLUDEMYTUTORIAL_SHADOWRENDERERCOMPONENT_H
