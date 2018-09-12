//
// Created by erick on 9/7/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_RENDERINGENGINE_H
#define MORDEROPENGLUDEMYTUTORIAL_RENDERINGENGINE_H


#include "Shaders/DirectionalLightShadowMapShader.h"
#include "../Core/Window.h"
#include "SkyBox.h"
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

    Shader* GetShader(ShaderType type);

    void RenderAmbientLight();

    void RenderScene();

    void RenderLights();

    void RenderEffects();

    void RenderAllMeshed();

    void SetCurrentShader(ShaderType type);

    void SetCurrentScene(Scene * scene);

private:
    //Shaders
    Shader* m_shaders[NUM_SHADER_TYPES];
    ShaderType m_current_shader;
    Scene * m_current_scene;

    //Profilers
    ProfileTimer m_renderProfileTimer;
//    ProfileTimer m_windowSyncProfileTimer;

    glm::mat4 m_projection;
    Window* m_window;
    Camera* m_camera;
    SkyBox* skybox;

    void CreateShaders();
    void SetupPerspective();
    void StartBlendColor();
    void EndBlendColor();
};


#endif //MORDEROPENGLUDEMYTUTORIAL_RENDERINGENGINE_H
