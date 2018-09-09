//
// Created by erick on 9/7/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_MESHRENDERER_H
#define MORDEROPENGLUDEMYTUTORIAL_MESHRENDERER_H


#include "GameComponent.h"
#include "../../Rendering/Mesh.h"
#include "../../Rendering/Material.h"
#include "../../Rendering/RenderingEngine.h"
#include "../CoreEngine.h"

class MeshRenderer: public GameComponent {
public:
    explicit MeshRenderer(GameObject* parent) : GameComponent(parent) {}


    virtual void Render(Shader* shader) const
    {
        shader->UpdateModel(m_parent->getTransform());

        if (shader->getType() != OMNI_DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER ||
                shader->getType() != DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER) {


            if (m_parent->getTransform().isNonUnformScaled()) {
                shader->UpdateNormalMatrix(
                        glm::mat3(glm::transpose(glm::inverse(m_parent->getTransform().GetModel())))
                );
            } else {
                shader->UpdateNormalMatrix(
                        glm::mat3(m_parent->getTransform().GetModel())
                );
             }

            m_parent->getMaterial().UseMaterial(shader);

            shader->resetDrawingTextureUnits();

        }

        m_parent->getMesh().Draw();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_MESHRENDERER_H
