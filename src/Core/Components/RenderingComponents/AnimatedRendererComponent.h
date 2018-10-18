//
// Created by erick on 9/30/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_ANIMATEDRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_ANIMATEDRENDERERCOMPONENT_H


#include "../../../Animation/AnimatedEntity.h"
#include "../../../Rendering/RenderingEngine.h"

class AnimatedRendererComponent: public EntityComponent<AnimatedEntity>  {
public:
    AnimatedRendererComponent(): EntityComponent(ANIMATED_RENDERER_COMPONENT){}

    void Render(RenderingEngine* engine) const override {
        auto * shader = engine->getShader(engine->getCurrentShaderType());

        shader->UpdateModel(m_entity->getTransform());

        if (shader->getType() != OMNI_DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER &&
            shader->getType() != DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER &&
            shader->getType() != TERRAIN_SHADER) {


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

        shader->Uniform1i("isAnimated",true);

        for(int i = 0; i < m_entity->getJoints().size(); i++){
            char locBuff[100] = {'\0'};
            snprintf(locBuff, sizeof(locBuff), "jointTransforms[%d]",m_entity->getJoints()[i]->getMeshIndex());
            shader->UniformMatrix4fv(locBuff,m_entity->getJoints()[i]->getAnimatedTransform());
        }

        m_entity->getMesh()->Draw();

        shader->Uniform1i("isAnimated",false);

    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_ANIMATEDRENDERERCOMPONENT_H
