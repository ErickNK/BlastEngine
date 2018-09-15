//
// Created by erick on 9/15/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_GUIRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_GUIRENDERERCOMPONENT_H


#include "../../Entities/GUIEntity.h"
#include "../../Input.h"
#include "../../../Rendering/Shaders/Shader.h"
#include "../EntityComponent.h"
#include "../../../Rendering/Shaders/GUIShader.h"

class GUIRendererComponent : public EntityComponent<GUIEntity,RenderingEngine>{
public:
    virtual void Render(RenderingEngine* engine) const {
        auto * shader = (GUIShader*) engine->GetShader(GUI_SHADER);

        engine->SetCurrentShader(GUI_SHADER);

        shader->Bind();

//            shader->UpdateProjection(glm::ortho(-1.0f,1.0f,-1.0f,1.0f));

            //Draw one by one.
            m_entity->getGUIMesh().Bind();

                for(GUIEntity* child: m_entity->getChildren()) {
                    shader->UpdateModel(child->getTransform());
                    child->getMaterial().UseMaterial(shader);
                    m_entity->getGUIMesh().Draw();
                }

            m_entity->getGUIMesh().UnBind();


        shader->UnBind();

    };
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GUIRENDERERCOMPONENT_H
