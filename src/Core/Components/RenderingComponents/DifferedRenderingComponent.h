//
// Created by erick on 10/10/18.
//

#ifndef BLASTENGINE_DIFFEREDRENDERINGCOMPONENT_H
#define BLASTENGINE_DIFFEREDRENDERINGCOMPONENT_H


#include "../../../Rendering/RenderingEngine.h"
#include "../../../Rendering/Shaders/DifferedShader.h"
#include "../../../Rendering/PostProcessing/Screen.h"
#include "../../../Rendering/DifferedRendering/DifferedScreen.h"
#include "../../../Rendering/Loaders/GUILoader.h"

class DifferedRenderingComponent {

public:
    void Init(){
        m_screen = new DifferedScreen();

        GLenum options[NUM_FBO_OPTIONS];

        options[TYPE] = GL_TEXTURE;
        options[TEXTURE_TYPE] = GL_TEXTURE_2D;
        options[INTERNAL_COMPONENT_FORMAT] = GL_RGB16F;
        options[EXTERNAL_COMPONENT_FORMAT] = GL_RGB;
        options[DATA_VALUE_FORMAT] = GL_FLOAT;
        options[ATTACHMENT_TYPE] = GL_COLOR_ATTACHMENT0;
        options[ENABLE_OVERLAY_FILTER] = GL_TRUE;
        options[ENABLE_WRAP_FILTER] = GL_TRUE;
        options[WRAP_FILTER] = GL_CLAMP_TO_BORDER;
        options[OVERLAY_FILTER] = GL_LINEAR;
        m_differedFBO.Generate(positionTexture, m_renderingEngine->getWindow()->getBufferWidth(),m_renderingEngine->getWindow()->getBufferHeight(),options);

        options[TYPE] = GL_TEXTURE;
        options[TEXTURE_TYPE] = GL_TEXTURE_2D;
        options[INTERNAL_COMPONENT_FORMAT] = GL_RGB16F;
        options[EXTERNAL_COMPONENT_FORMAT] = GL_RGB;
        options[DATA_VALUE_FORMAT] = GL_FLOAT;
        options[ATTACHMENT_TYPE] = GL_COLOR_ATTACHMENT1;
        options[ENABLE_OVERLAY_FILTER] = GL_TRUE;
        options[ENABLE_WRAP_FILTER] = GL_TRUE;
        options[WRAP_FILTER] = GL_CLAMP_TO_BORDER;
        options[OVERLAY_FILTER] = GL_LINEAR;
        m_differedFBO.Generate(normalTexture, m_renderingEngine->getWindow()->getBufferWidth(),m_renderingEngine->getWindow()->getBufferHeight(),options);

        options[TYPE] = GL_TEXTURE;
        options[TEXTURE_TYPE] = GL_TEXTURE_2D;
        options[INTERNAL_COMPONENT_FORMAT] = GL_RGBA;
        options[EXTERNAL_COMPONENT_FORMAT] = GL_RGBA;
        options[DATA_VALUE_FORMAT] = GL_UNSIGNED_BYTE;
        options[ATTACHMENT_TYPE] = GL_COLOR_ATTACHMENT2;
        options[ENABLE_OVERLAY_FILTER] = GL_TRUE;
        options[ENABLE_WRAP_FILTER] = GL_TRUE;
        options[WRAP_FILTER] = GL_CLAMP_TO_BORDER;
        options[OVERLAY_FILTER] = GL_LINEAR;
        m_differedFBO.Generate(diffuseTexture, m_renderingEngine->getWindow()->getBufferWidth(),m_renderingEngine->getWindow()->getBufferHeight(),options);

        options[TYPE] = GL_TEXTURE;
        options[TEXTURE_TYPE] = GL_TEXTURE_2D;
        options[INTERNAL_COMPONENT_FORMAT] = GL_RGBA;
        options[EXTERNAL_COMPONENT_FORMAT] = GL_RGBA;
        options[DATA_VALUE_FORMAT] = GL_UNSIGNED_BYTE;
        options[ATTACHMENT_TYPE] = GL_COLOR_ATTACHMENT3;
        options[ENABLE_OVERLAY_FILTER] = GL_TRUE;
        options[ENABLE_WRAP_FILTER] = GL_TRUE;
        options[WRAP_FILTER] = GL_CLAMP_TO_BORDER;
        options[OVERLAY_FILTER] = GL_LINEAR;
        m_differedFBO.Generate(specularTexture, m_renderingEngine->getWindow()->getBufferWidth(),m_renderingEngine->getWindow()->getBufferHeight(),options);

        options[TYPE] = GL_TEXTURE;
        options[TEXTURE_TYPE] = GL_TEXTURE_2D;
        options[INTERNAL_COMPONENT_FORMAT] = GL_RG16F;
        options[EXTERNAL_COMPONENT_FORMAT] = GL_RG;
        options[DATA_VALUE_FORMAT] = GL_FLOAT;
        options[ATTACHMENT_TYPE] = GL_COLOR_ATTACHMENT4;
        options[ENABLE_OVERLAY_FILTER] = GL_TRUE;
        options[ENABLE_WRAP_FILTER] = GL_TRUE;
        options[WRAP_FILTER] = GL_CLAMP_TO_BORDER;
        options[OVERLAY_FILTER] = GL_LINEAR;
        m_differedFBO.Generate(materialTexture, m_renderingEngine->getWindow()->getBufferWidth(),m_renderingEngine->getWindow()->getBufferHeight(),options);

        options[TYPE] = GL_TEXTURE;
        options[TEXTURE_TYPE] = GL_TEXTURE_2D;
        options[INTERNAL_COMPONENT_FORMAT] = GL_DEPTH_COMPONENT32;
        options[EXTERNAL_COMPONENT_FORMAT] = GL_DEPTH_COMPONENT;
        options[ATTACHMENT_TYPE] = GL_DEPTH_ATTACHMENT;
        options[DATA_VALUE_FORMAT] = GL_UNSIGNED_BYTE;
        options[ENABLE_OVERLAY_FILTER] = GL_TRUE;
        options[ENABLE_WRAP_FILTER] = GL_TRUE;
        options[WRAP_FILTER] = GL_CLAMP_TO_BORDER;
        options[OVERLAY_FILTER] = GL_LINEAR;
        m_differedFBO.Generate(depthTexture, m_renderingEngine->getWindow()->getBufferWidth(),m_renderingEngine->getWindow()->getBufferHeight(),options);

        m_screen->AddTexture(new Texture(m_differedFBO.GetTextures()[positionTexture],POSITION_TEXTURE));
        m_screen->AddTexture(new Texture(m_differedFBO.GetTextures()[normalTexture],NORMAL_MAP));
        m_screen->AddTexture(new Texture(m_differedFBO.GetTextures()[diffuseTexture],DIFFUSE_TEXTURE));
        m_screen->AddTexture(new Texture(m_differedFBO.GetTextures()[specularTexture],SPECULAR_TEXTURE));
        m_screen->AddTexture(new Texture(m_differedFBO.GetTextures()[materialTexture],MATERIAL_TEXTURE));
        m_screen->AddTexture(new Texture(m_differedFBO.GetTextures()[depthTexture],DEPTH_TEXTURE));

        GLenum someError = glGetError();
        assert( someError == GL_NO_ERROR);
    }

    void RenderScene() {

//        RenderShadows();

        m_renderingEngine->RenderSkybox();

    //GEOMETRY PASS
        m_differedFBO.BindFrameBuffer();

            std::vector<GLenum> buffers {
                GL_COLOR_ATTACHMENT0, //Position
                GL_COLOR_ATTACHMENT1, //Normal
                GL_COLOR_ATTACHMENT2, //Diffuse
                GL_COLOR_ATTACHMENT3, //Specular
                GL_COLOR_ATTACHMENT4  //Material
            };
            m_differedFBO.setForDrawing(true,buffers);

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if(m_renderingEngine->render_entities){
                auto * shader = (DifferedGeometryPassShader*) m_renderingEngine->BindShader(DIFFERED_GEOMETRYPASS_RENDERING_SHADER);

                    m_renderingEngine->RenderAllMeshed();

                m_renderingEngine->UnBindShader(DIFFERED_GEOMETRYPASS_RENDERING_SHADER);
            }

        m_differedFBO.UnBindFrameBuffer(m_renderingEngine->getWindow()->getBufferWidth(),m_renderingEngine->getWindow()->getBufferHeight());
    //END GEOMETRY PASS

    //LIGHT PASS
        if(m_renderingEngine->render_lights){
            auto * shader = (DifferedLightPassShader*) m_renderingEngine->BindShader(DIFFERED_LIGHTPASS_RENDERING_SHADER);

                //Set counts
                shader->Uniform1i("directionalLightCount",m_renderingEngine->getCurrentScene()->getDirectionalLightsCount());
                shader->Uniform1i("pointLightCount",m_renderingEngine->getCurrentScene()->getPointLightsCount());
                shader->Uniform1i("spotLightCount",m_renderingEngine->getCurrentScene()->getSpotLightsCount());

                //Set lights
                shader->SetLights(m_renderingEngine->getCurrentScene()->getLights());

                m_screen->Render(m_renderingEngine);

            m_renderingEngine->UnBindShader(DIFFERED_LIGHTPASS_RENDERING_SHADER);
        }
    //END LIGHT PASS

//        m_renderingEngine->RenderTerrain();
//
//        m_renderingEngine->RenderEffects();
//
//        m_renderingEngine->RenderWater();

        m_renderingEngine->RenderGUI();

        GLenum someError = glGetError();
        assert( someError == GL_NO_ERROR);
    }

    void setRenderingEngine(RenderingEngine *engine) {
        this->m_renderingEngine = engine;
    }

private:
    RenderingEngine * m_renderingEngine = nullptr;
    DifferedScreen * m_screen = nullptr;
    FrameBufferObject m_differedFBO;
    GLuint positionTexture, normalTexture, diffuseTexture, specularTexture, materialTexture, depthTexture;
    GUILoader* m_gui_loader = new GUILoader();
};


#endif //BLASTENGINE_DIFFEREDRENDERINGCOMPONENT_H
