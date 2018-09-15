//
// Created by erick on 9/10/18.
//

#include "EffectEntity.h"
#include "../Components/EntityComponent.h"

void EffectEntity::Render(RenderingEngine *engine) const
{
    for (auto m_component : m_components) {
        m_component->Render(engine);
    }
}

EffectEntity* EffectEntity::AddComponent(EntityComponent<EffectEntity,RenderingEngine> *component) {
    m_components.push_back(component);
    component->SetParent(this);
    return this;
}