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

    virtual void Render(RenderingEngine* engine) {}

    Transform& getTransform() { return m_transform; }

    void setTransform(Transform& transform) { m_transform = transform; }

    bool isAllowRender() const {
        return allow_render;
    }

    void setAllowRender(bool allow_render) {
        Entity::allow_render = allow_render;
    }

protected:

    Transform m_transform;

    bool allow_render = true;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_ENTITY_H
