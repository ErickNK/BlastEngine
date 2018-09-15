//
// Created by erick on 9/10/18.
//

#include "LightEntity.h"
#include "../Components/RenderingComponents/LightComponent.h"
#include "../Components/RenderingComponents/ShadowRendererComponent.h"

void LightEntity::ProcessInput(const Input* input, float delta)
{
//    m_transform.Update();

    for (auto &m_component : m_light_components) {
        m_component->ProcessInput(input, delta);
    }
}

void LightEntity::Update(float delta)
{
    for (auto &m_component : m_light_components) {
        m_component->Update(delta);
    }
}

void LightEntity::RenderLight(RenderingEngine* engine) const
{
    for (auto m_component : m_light_components) {
        m_component->Render(engine);
    }
}

void LightEntity::RenderShadow(RenderingEngine* engine) const
{
    for (auto m_component : m_shadow_components) {
        m_component->Render(engine);
    }
}


LightEntity *LightEntity::AddComponent(LightComponent *component) {
    m_light_components.push_back(component);
    component->SetParent((Light *)(this));
    return this;
}

LightEntity* LightEntity::AddShadowComponent(ShadowRendererComponent *component) {
    m_shadow_components.push_back(component);
    component->SetParent((Light *)(this));
    return this;
}
