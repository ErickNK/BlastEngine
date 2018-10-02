//
// Created by erick on 9/7/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_RENDERINGENGINE_H
#define MORDEROPENGLUDEMYTUTORIAL_RENDERINGENGINE_H


#include "Shaders/DirectionalLightShadowMapShader.h"
#include "../Core/Window.h"
#include "Shaders/ForwardAmbientShader.h"
#include "Shaders/ForwardDirectionalLightShader.h"
#include "Shaders/ForwardPointLightShader.h"
#include "Shaders/ForwardSpotLightShader.h"
#include "Lighting/DirectionalLight.h"
#include "../Common/ProfileTimer.h"
#include "../Core/Scene.h"

class GameObject;

class RenderingEngine {
public:
    explicit RenderingEngine(Window* window);

    inline double DisplayRenderTime(double dividend) { return m_renderProfileTimer.DisplayAndReset("Render Time: ", dividend); }

//    inline double DisplayWindowSyncTime(double dividend) { return m_windowSyncProfileTimer.DisplayAndReset("Window Sync Time: ", dividend); }

    Shader* BindShader(ShaderType type);

    void UnBindShader(ShaderType type);

    void EnableCulling();

    void DisableCulling();

    void RenderAmbientLight();

    void RenderScene();

    void RenderLights();

    void RenderEffects();

    void RenderAllMeshed();

    void RenderTerrain();

    void RenderGUI();

    void SetCurrentScene(Scene * scene);

    Scene *getCurrentScene() const;

    void ActivateClipPlane(int id, glm::vec4& plane);

    void DeactivateClipPlane(int id);

    bool render_terrain = true;
    bool render_water = true;
    bool render_lights = true;
    bool render_gui = true;
    bool render_effects = true;
    bool render_shadows = true;

    void CleanUP();

    Window *getWindow();

    Shader *getShader(ShaderType type);

    ShaderType getCurrentShaderType();

private:
    //Shaders
    Shader* m_shaders[NUM_SHADER_TYPES];
    ShaderType m_current_shader;

    //Profilers
    ProfileTimer m_renderProfileTimer;
//    ProfileTimer m_windowSyncProfileTimer;

    Scene * m_current_scene = nullptr;
    Window* m_window = nullptr;

    glm::vec4 m_clipping_Planes [MAX_CLIP_PLANES];
    bool m_activated_clipping_Planes [MAX_CLIP_PLANES];

    void RenderShadows();
    void RenderSkybox();
    void RenderWater();
    Shader* UpdateShader(Shader* shader);
    void CreateShaders();
    void StartAlphaBlending();
    void EndAlphaBlending();
};


#endif //MORDEROPENGLUDEMYTUTORIAL_RENDERINGENGINE_H
