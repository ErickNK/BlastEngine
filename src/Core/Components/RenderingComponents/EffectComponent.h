//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_EFFECTCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_EFFECTCOMPONENT_H

#include "../../Scene.h"
#include "../../Entities/EffectEntity.h"

class EffectComponent {
public:
    EffectComponent() = default;

    EffectComponent(EffectEntity* effectEntity) : m_parent(effectEntity) {}

    virtual void RenderEffect(RenderingEngine* engine) const {}

    virtual void SetParent(EffectEntity* parent) { m_parent = parent; }

protected:
    EffectEntity* m_parent;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_EFFECTCOMPONENT_H
