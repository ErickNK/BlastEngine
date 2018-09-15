//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SKYBOXCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_SKYBOXCOMPONENT_H

#include "../Input.h"
#include "../../Rendering/Shaders/Shader.h"

template <class Entity,class RenderParam = Shader>
class EntityComponent {
public:
    EntityComponent() = default;
    EntityComponent(Entity* entity) : m_entity(entity) {}
    virtual void ProcessInput(Input* input, float delta) {}
    virtual void Update(float delta) {}
    virtual void Render(RenderParam* shader) const {};
    virtual void SetParent(Entity* entity) { m_entity = entity; }
protected:
    Entity* m_entity{};
};


#endif //MORDEROPENGLUDEMYTUTORIAL_SKYBOXCOMPONENT_H
