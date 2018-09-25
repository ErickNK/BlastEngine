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
    EntityComponent(Entity* entity) : m_entity(entity),m_type() {}
    virtual void ProcessInput(Input* input, float delta) {}
    virtual void Update(double time, float delta) {}
    virtual void Render(RenderParam* shader) const {};
    virtual void SetParent(Entity* entity) { m_entity = entity; }
    virtual Entity *getParent() const { return m_entity; }
    ComponentTypes getType() { return m_type; }

protected:
    Entity* m_entity{};
    ComponentTypes m_type;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_SKYBOXCOMPONENT_H
