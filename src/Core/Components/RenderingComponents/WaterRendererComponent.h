//
// Created by erick on 9/22/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_WATERRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_WATERRENDERERCOMPONENT_H


#include "../../../Rendering/Primitives/Water.h"
#include "../../../Rendering/RenderingEngine.h"
#include "../../../Rendering/Shaders/WaterShader.h"

class WaterRendererComponent: public EntityComponent<Water,RenderingEngine>  {
public:
    void Update(double time, float delta) override {
        EntityComponent::Update(time, delta);

        m_entity->moveFactor += m_entity->wave_speed * delta;

        fmod(m_entity->moveFactor,1.0f);
    }

    void RenderWater(RenderingEngine* engine) const {
        engine->render_water = false;
        engine->render_gui = false;
        m_entity->allow_render = false;

        //REFLECTION
        m_entity->getReflectionFBO().BindFrameBuffer();
        m_entity->getReflectionFBO().setForDrawing(true,0);

            glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            engine->ActivateClipPlane(0,*new glm::vec4(0,1,0,-m_entity->getHeight() + 1.0f));

            Camera* camera = engine->getCurrentScene()->getCurrentCamera();
            float distance = 2 * (camera->getTransform().GetPos().y - m_entity->getHeight());
//
            camera->getTransform().GetPos().y -= distance;
            camera->invertPitch();
            camera->UpdateView();

            engine->RenderScene();

            camera->getTransform().GetPos().y += distance;
            camera->invertPitch();
            camera->UpdateView();

            engine->DeactivateClipPlane(0);

        m_entity->getReflectionFBO().UnBindFrameBuffer(engine->getWindow()->getBufferWidth(),engine->getWindow()->getBufferHeight());

        //REFRACTION
        m_entity->getRefractionFBO().BindFrameBuffer();
        m_entity->getRefractionFBO().setForDrawing(true,0);

            glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            engine->ActivateClipPlane(0,*new glm::vec4(0,-1,0,m_entity->getHeight() + 1.0f));

            engine->RenderScene();

            engine->DeactivateClipPlane(0);

        m_entity->getRefractionFBO().UnBindFrameBuffer(engine->getWindow()->getBufferWidth(),engine->getWindow()->getBufferHeight());

        //RENDER
        m_entity->allow_render = true;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        auto * shader = (WaterShader*) engine->BindShader(WATER_SHADER);

            shader->SetWater(m_entity);

            shader->SetLights(engine->getCurrentScene()->getLights());

            m_entity->RenderAll(shader);

        engine->UnBindShader(WATER_SHADER);

        glDisable(GL_BLEND);

        engine->render_gui = true;
        engine->render_water = true;

    }
};


#endif //MORDEROPENGLUDEMYTUTORIAL_WATERRENDERERCOMPONENT_H
