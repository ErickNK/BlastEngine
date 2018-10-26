//
// Created by erick on 9/22/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_WATERRENDERERCOMPONENT_H
#define MORDEROPENGLUDEMYTUTORIAL_WATERRENDERERCOMPONENT_H


#include "../../../Rendering/Primitives/Water.h"
#include "../../../Rendering/RenderingEngine.h"
#include "../../../Rendering/Shaders/WaterShader.h"
#include "../../../Common/Helpers.h"
#include "../../Components/RenderingComponents/DifferedRenderingComponent.h"

class WaterRendererComponent: public EntityComponent<Water>  {
public:

    explicit WaterRendererComponent(int m_water_rendering_component_id)
    : EntityComponent(WATER_RENDERER_COMPONENT),
    m_water_rendering_buffer(m_water_rendering_component_id) {}

    void Update(double time, float delta) override {
        EntityComponent::Update(time, delta);

        m_entity->moveFactor += m_entity->wave_speed * delta;

        m_entity->moveFactor = fmod(m_entity->moveFactor,1.0f);
    }

    void Render(RenderingEngine* engine) const override {
        engine->setFlag(RENDER_WATER, false);
        engine->setFlag(RENDER_GUI, false);
        m_entity->allowRender(false);

        if(!engine->getFlag(IS_SHADOW_PASS)){ //Render reflections and refractions only if not shadow pass.
            //REFLECTION
            engine->PushFBO(&m_entity->getReflectionFBO());

                std::vector<GLenum> reflectionBuffers {GL_COLOR_ATTACHMENT0};
                m_entity->getReflectionFBO().setForDrawing(true,reflectionBuffers);

                m_entity->getReflectionFBO().ClearFBO();

                engine->ActivateClipPlane(0,*new glm::vec4(0,1,0,-m_entity->getHeight() + 1.0f));

                    Camera* camera = engine->getCurrentScene()->getCurrentCamera();
                    float distance = 2 * (camera->getTransform().GetPos().y - m_entity->getHeight());

                    {
                        camera->getTransform().GetPos().y -= distance;
                        camera->invertPitch();
                        camera->UpdateView();
                    }

                        engine->PushRenderingComponent(m_water_rendering_buffer);

                            engine->RenderScene();

                        engine->PopRenderingComponent();

                    {
                        camera->getTransform().GetPos().y += distance;
                        camera->invertPitch();
                        camera->UpdateView();
                    }

                engine->DeactivateClipPlane(0);

            engine->PopFBO();

            //REFRACTION
            engine->PushFBO(&m_entity->getRefractionFBO());

                std::vector<GLenum> refractionBuffers {GL_COLOR_ATTACHMENT0};
                m_entity->getRefractionFBO().setForDrawing(true,refractionBuffers);

                m_entity->getReflectionFBO().ClearFBO();

                engine->ActivateClipPlane(0,*new glm::vec4(0,-1,0,m_entity->getHeight() + 1.0f));

                    engine->PushRenderingComponent(m_water_rendering_buffer);

                        engine->RenderScene();

                    engine->PopRenderingComponent();

                engine->DeactivateClipPlane(0);

            engine->PopFBO();
        }

        //RENDER
        m_entity->allowRender(true);

        engine->DeactivateAllClipPlanes();
        auto * shader = (WaterShader*) engine->PushShader(WATER_SHADER);

            shader->SetWater(m_entity);

            m_entity->getComponent(MESHED_RENDERER_COMPONENT)->Render(engine);

        engine->PopShader();

        engine->setFlag(RENDER_WATER, true);
        engine->setFlag(RENDER_GUI, true);
    }

private:
    int m_water_rendering_buffer;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_WATERRENDERERCOMPONENT_H
