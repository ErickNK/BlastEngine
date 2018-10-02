//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SKYBOXCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_SKYBOXCOMPONENT_H

#include "../Input.h"
#include "../../Rendering/Shaders/Shader.h"

class RenderingEngine;

template <class Entity>
class EntityComponent {
public:
    EntityComponent() = default;
    explicit EntityComponent(Entity* entity) : m_entity(entity),m_type(NONE) {}
    virtual void ProcessInput(Input* input, float delta) {}
    virtual void Update(double time, float delta) {}
    virtual void Render(RenderingEngine* engine) const {};
    virtual void SetParent(Entity* entity) { m_entity = entity; }
    virtual Entity *getParent() const { return m_entity; }
    ComponentTypes getType() { return m_type; }

protected:
    Entity* m_entity{};
    ComponentTypes m_type = NONE;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_SKYBOXCOMPONENT_H
