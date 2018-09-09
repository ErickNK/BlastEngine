//
// Created by erick on 9/7/18.
//

#include "RenderingEngine.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Common/CommonValues.h"
#include "../Core/Window.h"
#include "../Core/GameObject.h"
#include "Shaders/Shader.h"
#include "Transform.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Lighting/DirectionalLight.h"
#include "Lighting/PointLight.h"
#include "Lighting/SpotLight.h"
#include "SkyBox.h"

RenderingEngine::RenderingEngine(Window* window): m_window(window) {
    CreateShaders();
    SetupPerspective();
    SetupCamera();
    SetupSkyBox();
}

void RenderingEngine::CreateShaders(){
    m_directional_light_shadow_map_shader = DirectionalLightShadowMapShader();
    m_directional_light_shadow_map_shader.Init();

    m_forward_ambient_shader = ForwardAmbientShader();
    m_forward_ambient_shader.Init();

    m_directional_Light_shader = ForwardDirectionalLightShader();
    m_directional_Light_shader.Init();

    m_point_Light_shader = ForwardPointLightShader();
    m_point_Light_shader.Init();

    m_spot_Light_shader = ForwardSpotLightShader();
    m_spot_Light_shader.Init();
}

void RenderingEngine::SetupSkyBox() {
    std::vector<std::string> faceLocations;

    faceLocations.emplace_back("../res/textures/skybox/cloudtop_lf.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_rt.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_up.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_dn.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_ft.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_bk.tga");

    skybox = SkyBox(faceLocations);
}

void RenderingEngine::SetupPerspective(){
    //Setup projection
    m_projection = glm::perspective(
            45.0f,
            (GLfloat)m_window->getBufferWidth()/(GLfloat)m_window->getBufferHeight(),
            0.1f,
            1000.0f
    );
}

void RenderingEngine::SetupCamera(){
    m_camera = Camera(
            glm::vec3(2.0f,2.0f,5.0f),
            glm::vec3(0.0f,1.0f,0.0f),
            -90.0f,
            0.0f,
            15.0f,
            0.5f
    );
}

void RenderingEngine::StartBlendColor(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ONE);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_EQUAL); //Do blend function on pixels that appear closest to the screen.
}

void RenderingEngine::EndBlendColor(){
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void RenderingEngine::RenderAmbientLight(GameObject &object){
    m_forward_ambient_shader.Bind();

        m_forward_ambient_shader.UpdateProjection(m_projection);

        m_forward_ambient_shader.UpdateView(m_camera);

        m_forward_ambient_shader.setLight(glm::vec3(1,1,1),0.06);

        object.RenderAll(&m_forward_ambient_shader);

    m_forward_ambient_shader.UnBind();
}

void RenderingEngine::RenderDirectionalLightShadowMap(DirectionalLight* dlight,GameObject &object) {
    m_directional_light_shadow_map_shader.Bind();

        glClear(GL_DEPTH_BUFFER_BIT);

        //Set view port same size as our shadow-map framebuffer
        glViewport(0, 0, dlight->GetShadowMap()->GetShadowWidth(), dlight->GetShadowMap()->GetShadowHeight());

        dlight->GetShadowMap()->BindFrameBuffer(); //Begin writing

            m_directional_light_shadow_map_shader.SetDirectionalLight(dlight);

            object.RenderAll(&m_directional_light_shadow_map_shader);

        dlight->GetShadowMap()->UnBindFrameBuffer(); //stop writing

    m_directional_light_shadow_map_shader.UnBind();
}

void RenderingEngine::RenderDirectionalLight(DirectionalLight* dlight,GameObject &object){
    m_window->ResetViewPort();

    m_directional_Light_shader.Bind();

        m_directional_Light_shader.UpdateProjection(m_projection);

        m_directional_Light_shader.UpdateView(m_camera);

        m_directional_Light_shader.setLight(dlight);

        object.RenderAll(&m_directional_Light_shader);

    m_directional_Light_shader.UnBind();
}

void RenderingEngine::RenderPointLight(PointLight* plight,GameObject &object){
    m_window->ResetViewPort();

    m_point_Light_shader.Bind();

        m_point_Light_shader.UpdateProjection(m_projection);

        m_point_Light_shader.UpdateView(m_camera);

        m_point_Light_shader.setLight(plight);

        object.RenderAll(&m_point_Light_shader);

    m_point_Light_shader.UnBind();
}

void RenderingEngine::RenderSpotLight(SpotLight* slight,GameObject &object){
    m_window->ResetViewPort();

    m_spot_Light_shader.Bind();

        m_spot_Light_shader.UpdateProjection(m_projection);

        m_spot_Light_shader.UpdateView(m_camera);

        m_spot_Light_shader.setLight(slight);

        object.RenderAll(&m_spot_Light_shader);

    m_spot_Light_shader.UnBind();
}

void RenderingEngine::RenderScene(GameObject &object) {
    m_window->ResetViewPort();

    skybox.Draw(m_camera, m_projection);

    RenderAmbientLight(object);

    for (auto &m_directional_light : m_directional_lights) {
        StartBlendColor();

//            RenderDirectionalLightShadowMap(m_directional_light,object);

            RenderDirectionalLight(m_directional_light,object);

        EndBlendColor();
    }

    for (auto &m_point_light : m_point_lights) {
        StartBlendColor();

//            RenderDirectionalLightShadowMap(m_directional_light,object);

            RenderPointLight(m_point_light,object);

        EndBlendColor();
    }

    for (auto &m_spot_light : m_spot_lights) {
        StartBlendColor();

//            RenderDirectionalLightShadowMap(m_directional_light,object);

            RenderSpotLight(m_spot_light,object);

        EndBlendColor();
    }

}

void RenderingEngine::ProcessInput(Input* input,float delta){
    m_camera.handleMouse(input->getXChange(),input->getYChange());
    m_camera.handleKeys(input->getKeys(),delta);
//    spotLights[0].SetAsFlashLight(m_camera);
}

void RenderingEngine::Render(GameObject &object) {
    m_renderProfileTimer.StartInvocation();

        RenderScene(object);

    m_renderProfileTimer.StopInvocation();
}

