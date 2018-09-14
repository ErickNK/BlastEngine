//
// Created by erick on 9/7/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_MESHRENDERER_H
#define MORDEROPENGLUDEMYTUTORIAL_MESHRENDERER_H

#include "../../Entities/MeshedEntity.h"

class Shader;
class Input;

class MeshedComponent {
public:
    MeshedComponent() = default;
    MeshedComponent(MeshedEntity* meshedEntity) : m_meshedEntity(meshedEntity) {}
    virtual void ProcessInput(Input* input, float delta) {}
    virtual void Update(float delta) {}
    virtual void Render(Shader* shader) const {};
    virtual void SetParent(MeshedEntity* meshedEntity) { m_meshedEntity = meshedEntity; }
protected:
    MeshedEntity* m_meshedEntity{};
};


#endif //MORDEROPENGLUDEMYTUTORIAL_MESHRENDERER_H
