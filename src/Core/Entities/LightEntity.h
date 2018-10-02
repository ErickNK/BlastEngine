//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_LIGHTENTITY_H
#define MORDEROPENGLUDEMYTUTORIAL_LIGHTENTITY_H


#include "../Input.h"
#include "../../Rendering/Shaders/Shader.h"
#include "../Components/EntityComponent.h"
#include "Entity.h"

class ShadowRendererComponent;
class CoreEngine;
class RenderingEngine;
class Scene;
class Light;

class LightEntity: public Entity {
public:

    void ProcessInput(Input* input, float delta) override;

    void Update(double time, float delta) override;

    void RenderLight(RenderingEngine* engine) const;

    void RenderShadow(RenderingEngine* engine) const;

    LightEntity* AddComponent(EntityComponent<Light>* component);

    LightEntity* AddShadowComponent(ShadowRendererComponent* component);


protected:
    std::vector<EntityComponent<Light>*> m_light_components;

    std::vector<ShadowRendererComponent*> m_shadow_components;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_LIGHTENTITY_H
