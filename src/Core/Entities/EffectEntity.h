//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_EFFECTENTITY_H
#define MORDEROPENGLUDEMYTUTORIAL_EFFECTENTITY_H

#include "../Input.h"
#include "../../Rendering/Shaders/Shader.h"
#include "../Components/EntityComponent.h"

class CoreEngine;
class RenderingEngine;
class Scene;

class EffectEntity {
public:

    void Render(RenderingEngine *engine) const;

    EffectEntity* AddComponent(EntityComponent<EffectEntity>* component);

private:
    std::vector<EntityComponent<EffectEntity>*> m_components;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_EFFECTENTITY_H
