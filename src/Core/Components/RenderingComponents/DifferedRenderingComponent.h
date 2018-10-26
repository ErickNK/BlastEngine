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
#include "../../../Common/Helpers.h"

/**
 * A component that performs a differed rendering. By itself it acts as a
 * G-Buffer.
 * */
class DifferedRenderingComponent {
public:

    DifferedRenderingComponent(int id, RenderingEngine* engine): m_id(id), m_renderingEngine(engine){
        Init();
    }

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

        options[TYPE] = GL_TEXTURE;
        options[TEXTURE_TYPE] = GL_TEXTURE_2D_ARRAY;
        options[INTERNAL_COMPONENT_FORMAT] = GL_DEPTH_COMPONENT32;
        options[EXTERNAL_COMPONENT_FORMAT] = GL_DEPTH_COMPONENT;
        options[DATA_VALUE_FORMAT] = GL_UNSIGNED_BYTE;
        options[ATTACHMENT_TYPE] = GL_DEPTH_ATTACHMENT;
        options[NUM_OF_TEXTURES] = MAX_LIGHTS_PER_DRAW;
        options[ENABLE_OVERLAY_FILTER] = GL_TRUE;
        options[ENABLE_WRAP_FILTER] = GL_TRUE;
        options[WRAP_FILTER] = GL_CLAMP_TO_BORDER;
        options[OVERLAY_FILTER] = GL_LINEAR;
        m_layeredFBO.Generate(shadowMapsTextureArray, m_renderingEngine->getWindow()->getBufferWidth(),m_renderingEngine->getWindow()->getBufferHeight(),options);

        options[TYPE] = GL_TEXTURE;
        options[TEXTURE_TYPE] = GL_TEXTURE_2D_ARRAY;
        options[INTERNAL_COMPONENT_FORMAT] = GL_RGBA16F;
        options[EXTERNAL_COMPONENT_FORMAT] = GL_RGBA;
        options[DATA_VALUE_FORMAT] = GL_FLOAT;
        options[ATTACHMENT_TYPE] = GL_COLOR_ATTACHMENT5;
        options[NUM_OF_TEXTURES] = MAX_LIGHTS_PER_DRAW;
        options[ENABLE_OVERLAY_FILTER] = GL_TRUE;
        options[ENABLE_WRAP_FILTER] = GL_TRUE;
        options[WRAP_FILTER] = GL_CLAMP_TO_BORDER;
        options[OVERLAY_FILTER] = GL_LINEAR;
        m_layeredFBO.Generate(lightSpacePositionTextureArray, m_renderingEngine->getWindow()->getBufferWidth(),m_renderingEngine->getWindow()->getBufferHeight(),options);

        m_screen->AddTexture(new Texture(m_differedFBO.GetTextures()[positionTexture],POSITION_TEXTURE));
        m_screen->AddTexture(new Texture(m_differedFBO.GetTextures()[normalTexture],NORMAL_MAP));
        m_screen->AddTexture(new Texture(m_differedFBO.GetTextures()[diffuseTexture],DIFFUSE_TEXTURE));
        m_screen->AddTexture(new Texture(m_differedFBO.GetTextures()[specularTexture],SPECULAR_TEXTURE));
        m_screen->AddTexture(new Texture(m_differedFBO.GetTextures()[materialTexture],MATERIAL_TEXTURE));
        m_screen->AddTexture(new Texture(m_differedFBO.GetTextures()[depthTexture],DEPTH_TEXTURE));
        m_screen->AddTexture(new Texture(m_layeredFBO.GetTextures()[shadowMapsTextureArray],SHADOW_MAP_TEXTURE_ARRAY));
        m_screen->AddTexture(new Texture(m_layeredFBO.GetTextures()[lightSpacePositionTextureArray],LIGHT_SPACE_POSITION_TEXTURE_ARRAY));

        glCheckError();

    }

    void RenderScene() {

    //SHADOW PASS
        m_renderingEngine->setFlag(IS_SHADOW_PASS,true);

            m_renderingEngine->PushFBO(&m_layeredFBO);

                m_differedFBO.setForDrawing(false,buffers);

                m_differedFBO.ClearFBO();

                auto * differedShadowPassShader = (DifferedShadowPassShader*) m_renderingEngine->PushShader(DIFFERED_SHADOWPASS_RENDERING_SHADER);

                    differedShadowPassShader->SetEngine(m_renderingEngine);

                    m_renderingEngine->RenderAllMeshed();

                m_renderingEngine->PopShader();

            m_renderingEngine->PopFBO();

        m_renderingEngine->setFlag(IS_SHADOW_PASS, false);

    //END SHADOW PASS

    //GEOMETRY PASS
        m_renderingEngine->setFlag(IS_GEOMETRY_PASS,true);

            m_renderingEngine->PushFBO(&m_differedFBO);

                m_differedFBO.setForDrawing(true,buffers);

                m_differedFBO.ClearFBO();

                auto * differedGeometryPassShader = (DifferedGeometryPassShader*) m_renderingEngine->PushShader(DIFFERED_GEOMETRYPASS_RENDERING_SHADER);

                    differedGeometryPassShader->SetEngine(m_renderingEngine);

                    m_renderingEngine->RenderAllMeshed();

                m_renderingEngine->PopShader();

            m_renderingEngine->PopFBO();

        m_renderingEngine->setFlag(IS_GEOMETRY_PASS,false);
    //END GEOMETRY PASS

    //LIGHT PASS
        m_renderingEngine->setFlag(IS_LIGHT_PASS,true);

            auto * differedLightPassShader = (DifferedLightPassShader*) m_renderingEngine->PushShader(DIFFERED_LIGHTPASS_RENDERING_SHADER);

                differedLightPassShader->SetEngine(m_renderingEngine);

                m_screen->Render(m_renderingEngine);

            m_renderingEngine->PopShader();

        m_renderingEngine->setFlag(IS_LIGHT_PASS,false);
    //END LIGHT PASS

//        m_renderingEngine->RenderEffects();

//        m_renderingEngine->RenderWater();

//        m_renderingEngine->RenderSkybox();

        m_renderingEngine->setFlag(RENDER_GUI,true);
        m_renderingEngine->RenderGUI();

        glCheckError();

    }

    void setRenderingEngine(RenderingEngine *engine) { this->m_renderingEngine = engine; }

private:
    int m_id;

    RenderingEngine * m_renderingEngine = nullptr;

    DifferedScreen * m_screen = nullptr;

    FrameBufferObject m_differedFBO;
    FrameBufferObject m_layeredFBO;

    GLuint positionTexture = 0,
        normalTexture = 0,
        diffuseTexture = 0,
        specularTexture = 0,
        materialTexture = 0,
        depthTexture = 0,
        shadowMapsTextureArray = 0,
        lightSpacePositionTextureArray = 0;

    std::vector<GLenum> buffers {
            GL_COLOR_ATTACHMENT0, //Position
            GL_COLOR_ATTACHMENT1, //Normal
            GL_COLOR_ATTACHMENT2, //Diffuse
            GL_COLOR_ATTACHMENT3, //Specular
            GL_COLOR_ATTACHMENT4,  //Material
            GL_COLOR_ATTACHMENT5  //LightSpace positions
    };
};


#endif //BLASTENGINE_DIFFEREDRENDERINGCOMPONENT_H
