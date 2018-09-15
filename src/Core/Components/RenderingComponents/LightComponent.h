//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_LIGHTCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_LIGHTCOMPONENT_H


#include "../../../Rendering/Lighting/Light.h"
#include "../../../Rendering/Shaders/ForwardDirectionalLightShader.h"
#include "../../CoreEngine.h"

class LightComponent {
public:
    LightComponent() = default;
    explicit LightComponent(Light* light) : m_light(light) {}
    virtual ~LightComponent() = default;

    virtual void ProcessInput(const Input* input, float delta) {}
    virtual void Update(float delta) {}
    virtual void Render(RenderingEngine* engine) const {
        switch(m_light->getType()){
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

    virtual void SetParent(Light* parent) { m_light = parent; }

protected:
    Light* m_light{};

    virtual void RenderDirectionalLight(RenderingEngine* engine) const{
        auto * directional_light_shader = (ForwardDirectionalLightShader*) engine->GetShader(FORWARD_DIRECTIONAL_LIGHT_SHADER);

        engine->SetCurrentShader(FORWARD_DIRECTIONAL_LIGHT_SHADER);

        directional_light_shader->Bind();

            directional_light_shader->setLight(dynamic_cast<DirectionalLight *>(m_light));

            engine->RenderAllMeshed();

        directional_light_shader->UnBind();
    }

    virtual void RenderPointLight(RenderingEngine* engine) const {
        auto * point_light_shader = (ForwardPointLightShader*) engine->GetShader(FORWARD_POINT_LIGHT_SHADER);

        engine->SetCurrentShader(FORWARD_POINT_LIGHT_SHADER);

        point_light_shader->Bind();

            point_light_shader->setLight(dynamic_cast<PointLight *>(m_light));

            engine->RenderAllMeshed();

        point_light_shader->UnBind();
    }

    virtual void RenderSpotLight(RenderingEngine* engine) const {
        auto * spot_light_shader = (ForwardSpotLightShader*) engine->GetShader(FORWARD_SPOT_LIGHT_SHADER);

        engine->SetCurrentShader(FORWARD_SPOT_LIGHT_SHADER);

        spot_light_shader->Bind();

            spot_light_shader->setLight(dynamic_cast<SpotLight *>(m_light));

            engine->RenderAllMeshed();

        spot_light_shader->UnBind();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_LIGHTCOMPONENT_H
