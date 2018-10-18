//
// Created by erick on 9/16/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ENTITY_H
#define MORDEROPENGLUDEMYTUTORIAL_ENTITY_H


#include "../../Rendering/Transform.h"
#include "../Input.h"

class RenderingEngine;

class Entity {
public:

    Entity() = default;

    virtual void ProcessInput(Input* input, float delta) {}

    virtual void Update(double time, float delta) {}

    virtual void Render(RenderingEngine* engine) const {}

    Transform& getTransform() { return m_transform; }

    void setTransform(Transform& transform) { m_transform = transform; }

    bool isRenderAllowed() const { return allow_render; }

    void allowRender(bool allow_render) { Entity::allow_render = allow_render; }

    bool isUpdateAllowed() const { return allow_update; }

    void allowUpdate(bool allow_update) { Entity::allow_update = allow_update; }

    bool isInputAllowed() const { return allow_input; }

    void allowInput(bool allow_input) { Entity::allow_input = allow_input; }

protected:

    Transform m_transform;

    bool allow_render = true;

    bool allow_update = true;

    bool allow_input = true;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_ENTITY_H
