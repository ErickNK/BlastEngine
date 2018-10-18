//
// Created by erick on 9/7/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_RENDERINGENGINE_H
#define MORDEROPENGLUDEMYTUTORIAL_RENDERINGENGINE_H

#include <stack>
#include "Shaders/DirectionalLightShadowMapShader.h"
#include "../Core/Window.h"
#include "Shaders/ForwardAmbientShader.h"
#include "Shaders/ForwardDirectionalLightShader.h"
#include "Shaders/ForwardPointLightShader.h"
#include "Shaders/ForwardSpotLightShader.h"
#include "Lighting/DirectionalLight.h"
#include "../Common/ProfileTimer.h"
#include "../Core/Scene.h"

class DifferedRenderingComponent;

class RenderingEngine {
public:
    RenderingEngine() = default;

    void Initialize();

    Shader* BindShader(ShaderType type);

    void UnBindShader(ShaderType type);

    Shader* PushShader(ShaderType type);

    void PopShader();

    void ReplaceTopFBO(FrameBufferObject* fbo);

    void ResetTopToOriginalFBO();

    void PushFBO(FrameBufferObject* fbo);

    void PopFBO();

    void PushRenderingComponent(int id);

    void PopRenderingComponent();

    void RequestRenderingComponent(int &id);

    int RequestRenderingComponent();

    void EnableCulling();

    void DisableCulling();

    void RenderAmbientLight();

    void RenderScene();

    void RenderLights();

    void RenderEffects();

    void RenderAllMeshed();

    void RenderTerrain();

    void RenderShadows();

    void RenderSkybox();

    void RenderWater();

    void RenderGUI();

    void SetCurrentScene(Scene * scene);

    Scene *getCurrentScene() const;

    void ActivateClipPlane(int id, glm::vec4& plane);

    void DeactivateClipPlane(int id);

    void DeactivateAllClipPlanes();

    bool render_terrain = true;
    bool render_water = true;
    bool render_lights = true;
    bool render_gui = true;
    bool render_effects = true;
    bool render_shadows = true;
    bool render_entities = true;

    void CleanUP();

    Window *getWindow();

    void setWindow(Window * window);

    Shader *getShader(ShaderType type);

    ShaderType getCurrentShaderType();

private:
    //Shaders
    Shader* m_shaders[NUM_SHADER_TYPES] {};
    std::stack<ShaderType> m_current_shader;

    //FBOs
    std::vector<FrameBufferObject*> m_current_fbos;

    //Rendering Components
    std::map<int,DifferedRenderingComponent*> m_renderingComponents;
    std::vector<int> m_current_renderingComponents_ids;

    Scene * m_current_scene = nullptr;
    Window* m_window = nullptr;

    glm::vec4 m_clipping_Planes [MAX_CLIP_PLANES] {};
    bool m_activated_clipping_Planes [MAX_CLIP_PLANES] {};

    Shader* UpdateShader(Shader* shader);
    void CreateShaders();
    void StartAlphaBlending();
    void EndAlphaBlending();
    Shader* BindShader();
    void BindFBO();
};


#endif //MORDEROPENGLUDEMYTUTORIAL_RENDERINGENGINE_H
