//
// Created by erick on 9/16/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ENTITY_H
#define MORDEROPENGLUDEMYTUTORIAL_ENTITY_H


#include "../../Rendering/Transform.h"
#include "../Input.h"

class Entity {
public:

    Entity() = default;

    virtual void ProcessInput(Input* input, float delta) {}

    virtual void Update(double time, float delta) {}

    Transform& getTransform() { return m_transform; }

    void setTransform(Transform& transform) { m_transform = transform; }

protected:
    Transform m_transform;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_ENTITY_H
