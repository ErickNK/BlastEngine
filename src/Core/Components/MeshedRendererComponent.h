//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_MESHEDRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_MESHEDRENDERERCOMPONENT_H


#include "../Entities/MeshedEntity.h"
#include "MeshedComponent.h"

class MeshedRendererComponent: public MeshedComponent {
public:
    MeshedRendererComponent() = default;
    explicit MeshedRendererComponent(MeshedEntity* meshedEntity) : MeshedComponent(meshedEntity) {}

    virtual void Render(Shader* shader) const
    {
        shader->UpdateModel(m_meshedEntity->getTransform());

        if (shader->getType() != OMNI_DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER &&
            shader->getType() != DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER &&
            shader->getType() != TERRAIN_SHADER) {


            if (m_meshedEntity->getTransform().isNonUnformScaled()) {
                shader->UpdateNormalMatrix(
                        glm::mat3(glm::transpose(glm::inverse(m_meshedEntity->getTransform().GetModel())))
                );
            } else {
                shader->UpdateNormalMatrix(
                        glm::mat3(m_meshedEntity->getTransform().GetModel())
                );
            }

            m_meshedEntity->getMaterial().UseMaterial(shader);

            shader->resetDrawingTextureUnits();

        }

        m_meshedEntity->getMesh().Draw();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_MESHEDRENDERERCOMPONENT_H
