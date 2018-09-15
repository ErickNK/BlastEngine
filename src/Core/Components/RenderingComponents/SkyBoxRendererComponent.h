//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SKYBOXRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_SKYBOXRENDERERCOMPONENT_H


#include "../../../Rendering/RenderingEngine.h"
#include "../../../Rendering/Shaders/SkyBoxShader.h"

class SkyBoxRendererComponent {
public:
    void Render(RenderingEngine* engine)
    {

        auto * shader = (SkyBoxShader*) engine->GetShader(SKY_BOX_SHADER);

        engine->SetCurrentShader(SKY_BOX_SHADER);

        glDepthMask(GL_FALSE);
        shader->Bind();

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

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyBox->getTexture());

            m_skyBox->getSkyMesh()->Draw();

        shader->UnBind();
        glDepthMask(GL_TRUE);

    }

    void SetParent(SkyBox *parent) {
        m_skyBox = parent;
    }

private:
    SkyBox* m_skyBox;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_SKYBOXRENDERERCOMPONENT_H
