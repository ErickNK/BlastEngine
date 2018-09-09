//
// Created by erick on 9/7/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GAMECOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_GAMECOMPONENT_H


#include "../../Rendering/Shaders/Shader.h"
#include "../Input.h"

class GameObject;
class CoreEngine;

class GameComponent
{
public:
    GameComponent() = default;
    GameComponent(GameObject* parent) : m_parent(parent) {}
    virtual ~GameComponent() {}

    virtual void ProcessInput(const Input* input, float delta) {}
    virtual void Update(float delta) {}
    virtual void Render(Shader* shader) const {}

    virtual void SetParent(GameObject* parent) { m_parent = parent; }
    virtual GameObject* GetParent() { return m_parent; }
    virtual void AddToEngine(CoreEngine* engine) { }

protected:
    GameObject* m_parent{};
};

#endif //MORDEROPENGLUDEMYTUTORIAL_GAMECOMPONENT_H
