//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SKYBOXRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_SKYBOXRENDERERCOMPONENT_H


#include "../../../Rendering/RenderingEngine.h"
#include "../../../Rendering/Shaders/SkyBoxShader.h"

class SkyBoxRendererComponent : public EntityComponent<SkyBox>{
public:
    SkyBoxRendererComponent() : EntityComponent(SKYBOX_RENDERER_COMPONENT) {}

    void Render(RenderingEngine* engine) const override {

        glDepthMask(GL_FALSE);
        auto * shader = (SkyBoxShader*) engine->PushShader(SKY_BOX_SHADER);

            glm::mat4 view = engine->getCurrentScene()->getCurrentCamera()->getViewMatrix();
            view = glm::mat4(glm::mat3(view));

            glm::mat4 projection = engine->getCurrentScene()->getCurrentCamera()->getProjection();

            //TODO: solve projection from camera issue
            shader->UpdateProjection(glm::perspective(
                    engine->getCurrentScene()->getCurrentCamera()->field_of_view,
                    engine->getCurrentScene()->getCurrentCamera()->aspect,
                    engine->getCurrentScene()->getCurrentCamera()->near_clip,
                    engine->getCurrentScene()->getCurrentCamera()->far_clip
                    ));

            shader->UpdateView(view);

            shader->UpdateModel(m_entity->getTransform());

            shader->SetSkyBox(m_entity);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_entity->getTextures()[DAY_SKYBOX]);

            glActiveTexture(GL_TEXTURE0 + 1);
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_entity->getTextures()[NIGHT_SKYBOX]);

            m_entity->getSkyMesh()->Draw();

        engine->PopShader();
        glDepthMask(GL_TRUE);

    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_SKYBOXRENDERERCOMPONENT_H
