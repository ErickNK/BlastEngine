//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_LIGHTENTITY_H
#define MORDEROPENGLUDEMYTUTORIAL_LIGHTENTITY_H


#include "../Input.h"
#include "../../Rendering/Shaders/Shader.h"

class CoreEngine;
class RenderingEngine;
class LightComponent;
class Scene;

class LightEntity {
public:

    void ProcessInput(const Input* input, float delta);

    void Update(float delta);

    void RenderLight(RenderingEngine* engine) const;

    LightEntity* AddComponent(LightComponent* component);

protected:
    std::vector<LightComponent*> m_components;

    Transform m_transform;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_LIGHTENTITY_H
