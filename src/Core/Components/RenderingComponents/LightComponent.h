//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_LIGHTCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_LIGHTCOMPONENT_H

#include "../../../Rendering/Shaders/ForwardDirectionalLightShader.h"
#include "../../CoreEngine.h"

class LightComponent:public EntityComponent<LightEntity>{
public:
    LightComponent(): EntityComponent(LIGHT_COMPONENT){}

    void Render(RenderingEngine* engine) const override {
        switch(m_entity->getType()){
            case DIRECTIONAL_LIGHT:
                RenderDirectionalLight(engine);
            break;

            case POINT_LIGHT:
                RenderPointLight(engine);
            break;

            case SPOT_LIGHT:
                RenderSpotLight(engine);
            break;

            case NUM_LIGHT_TYPES:break;
            default: break;
        }
    }

    virtual void SetParent(LightEntity* parent) { m_entity = parent; }

protected:
    virtual void RenderDirectionalLight(RenderingEngine* engine) const{
        auto * directional_light_shader = (ForwardDirectionalLightShader*) engine->PushShader(FORWARD_DIRECTIONAL_LIGHT_SHADER);

            directional_light_shader->setLight(dynamic_cast<DirectionalLight *>(m_entity));

            engine->RenderAllMeshed();

        engine->PopShader();
    }

    virtual void RenderPointLight(RenderingEngine* engine) const {
        auto * point_light_shader = (ForwardPointLightShader*) engine->PushShader(FORWARD_POINT_LIGHT_SHADER);

            point_light_shader->setLight(dynamic_cast<PointLight *>(m_entity));

            engine->RenderAllMeshed();

        engine->PopShader();
    }

    virtual void RenderSpotLight(RenderingEngine* engine) const {
        auto * spot_light_shader = (ForwardSpotLightShader*) engine->PushShader(FORWARD_SPOT_LIGHT_SHADER);

            spot_light_shader->setLight(dynamic_cast<SpotLight *>(m_entity));

            engine->RenderAllMeshed();

        engine->PopShader();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_LIGHTCOMPONENT_H
