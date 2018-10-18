//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_MESHEDRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_MESHEDRENDERERCOMPONENT_H


#include "../../Entities/MeshedEntity.h"
#include "../EntityComponent.h"
#include "../../../Rendering/RenderingEngine.h"

class MeshedRendererComponent: public EntityComponent<MeshedEntity> {
public:
    MeshedRendererComponent(): EntityComponent(MESHED_RENDERER_COMPONENT){}

    void Render(RenderingEngine* engine) const override {
        auto * shader = engine->getShader(engine->getCurrentShaderType());

        shader->UpdateModel(m_entity->getTransform());

        if (shader->getType() != OMNI_DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER &&
            shader->getType() != DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER) {


            if (m_entity->getTransform().isNonUnformScaled()) {
                shader->UpdateNormalMatrix(
                        glm::mat3(glm::transpose(glm::inverse(m_entity->getTransform().GetModel())))
                );
            } else {
                shader->UpdateNormalMatrix(
                        glm::mat3(m_entity->getTransform().GetModel())
                );
            }

            m_entity->getMaterial()->UseMaterial(shader);

            shader->resetDrawingTextureUnits();

        }

        m_entity->getMesh()->Draw();
    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_MESHEDRENDERERCOMPONENT_H
