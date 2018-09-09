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

class GameObject;

class RenderingEngine {
public:
    explicit RenderingEngine(Window* window);

    void Render(GameObject &object);

    void ProcessInput(Input* input,float delta);

    inline double DisplayRenderTime(double dividend) { return m_renderProfileTimer.DisplayAndReset("Render Time: ", dividend); }

//    inline double DisplayWindowSyncTime(double dividend) { return m_windowSyncProfileTimer.DisplayAndReset("Window Sync Time: ", dividend); }

    inline void AddDirectionalLight(DirectionalLight* light) { m_directional_lights.push_back(light); }
    inline void AddPointLight(PointLight* light) { m_point_lights.push_back(light); }
    inline void AddSpotLight(SpotLight* light) { m_spot_lights.push_back(light); }

private:
    //Shaders
    DirectionalLightShadowMapShader m_directional_light_shadow_map_shader;
    ForwardAmbientShader m_forward_ambient_shader;
    ForwardDirectionalLightShader m_directional_Light_shader;
    ForwardPointLightShader m_point_Light_shader;
    ForwardSpotLightShader m_spot_Light_shader;

    //Profilers
    ProfileTimer m_renderProfileTimer;
//    ProfileTimer m_windowSyncProfileTimer;


    glm::mat4 m_projection;
    Window* m_window;
    Camera m_camera;
    SkyBox skybox;


    //Lights
    std::vector<DirectionalLight*> m_directional_lights;
    std::vector<PointLight*> m_point_lights;
    std::vector<SpotLight*> m_spot_lights;

    void CreateShaders();
    void SetupSkyBox();
    void SetupPerspective();
    void SetupCamera();
    void StartBlendColor();
    void EndBlendColor();
    void RenderScene(GameObject &object);
    void RenderAmbientLight(GameObject &object);
    void RenderDirectionalLight(DirectionalLight* dlight,GameObject &object);
    void RenderPointLight(PointLight* plight,GameObject &object);
    void RenderSpotLight(SpotLight* slight,GameObject &object);
    void RenderDirectionalLightShadowMap(DirectionalLight* dlight,GameObject &object);
};


#endif //MORDEROPENGLUDEMYTUTORIAL_RENDERINGENGINE_H
