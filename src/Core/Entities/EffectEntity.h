//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_EFFECTENTITY_H
#define MORDEROPENGLUDEMYTUTORIAL_EFFECTENTITY_H

#include "../Input.h"
#include "../../Rendering/Shaders/Shader.h"
class CoreEngine;
class RenderingEngine;
class EffectComponent;
class Scene;

class EffectEntity {
public:

    void RenderEffect(RenderingEngine* engine) const;

    EffectEntity* AddComponent(EffectComponent* component);

private:
    std::vector<EffectComponent*> m_components;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_EFFECTENTITY_H
