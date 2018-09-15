//
// Created by erick on 9/10/18.
//

#include "EffectEntity.h"
#include "../Components/EffectComponent.h"

void EffectEntity::RenderEffect(RenderingEngine* engine) const
{
    for (auto m_component : m_components) {
        m_component->RenderEffect(engine);
    }
}

EffectEntity* EffectEntity::AddComponent(EffectComponent *component) {
    m_components.push_back(component);
    component->SetParent(this);
    return this;
}