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

class GUIRendererComponent : public EntityComponent<GUIEntity>{
public:
    GUIRendererComponent() : EntityComponent(GUI_RENDERER_COMPONENT) {}

    void Render(RenderingEngine* engine) const override {
        auto * shader = (GUIShader*) engine->PushShader(GUI_SHADER);

            //Draw one by one.
            m_entity->getGUIMesh().Bind();

                for(GUIEntity* child: m_entity->getChildren()) {
                    shader->UpdateModel(child->getTransform());
                    child->getMaterial().UseMaterial(shader);
                    m_entity->getGUIMesh().Draw();
                }

            m_entity->getGUIMesh().UnBind();


        engine->PopShader();

    };
};


#endif //MORDEROPENGLUDEMYTUTORIAL_GUIRENDERERCOMPONENT_H
