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
#include "../Core/Scene.h"
#include "Shaders/Shader.h"
#include "Camera.h"
#include "SkyBox.h"
#include "Shaders/FogShader.h"

RenderingEngine::RenderingEngine(Window* window): m_window(window) {
    CreateShaders();
    SetupPerspective();
    SetupCamera();
    SetupSkyBox();
}

void RenderingEngine::CreateShaders(){

    auto  * directionalLightShadowMapShader = new DirectionalLightShadowMapShader();
    directionalLightShadowMapShader->Init();
    m_shaders[DIRECTIONAL_LIGHT_SHADOW_MAP_SHADER] = directionalLightShadowMapShader;

    auto * forwardAmbientShader = new ForwardAmbientShader();
    forwardAmbientShader->Init();
    m_shaders[FORWARD_AMBIENT_SHADER] = forwardAmbientShader;

    auto * forwardDirectionalLightShader = new ForwardDirectionalLightShader();
    forwardDirectionalLightShader->Init();
    m_shaders[FORWARD_DIRECTIONAL_LIGHT_SHADER] = forwardDirectionalLightShader;

    auto * forwardPointLightShader = new ForwardPointLightShader();
    forwardPointLightShader->Init();
    m_shaders[FORWARD_POINT_LIGHT_SHADER] = forwardPointLightShader;

    auto * forwardSpotLightShader = new ForwardSpotLightShader();
    forwardSpotLightShader->Init();
    m_shaders[FORWARD_SPOT_LIGHT_SHADER] = forwardSpotLightShader;

    auto  * fogShader = new FogShader();
    fogShader->Init();
    m_shaders[FOG_SHADER] = fogShader;
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

void RenderingEngine::RenderAmbientLight(){
    auto * ambient_light_shader = (ForwardAmbientShader*)  m_shaders[FORWARD_AMBIENT_SHADER];

    m_current_shader = FORWARD_AMBIENT_SHADER;

    ambient_light_shader->Bind();

        ambient_light_shader->setLight(glm::vec3(1,1,1),0.06);

        RenderAllMeshed();

    ambient_light_shader->UnBind();
}

//void RenderingEngine::RenderDirectionalLightShadowMap(DirectionalLight* dlight,GameObject &object) {
//    m_directional_light_shadow_map_shader.Bind();
//
//        glClear(GL_DEPTH_BUFFER_BIT);
//
//        //Set view port same size as our shadow-map framebuffer
//        glViewport(0, 0, dlight->GetShadowMap()->GetShadowWidth(), dlight->GetShadowMap()->GetShadowHeight());
//
//        dlight->GetShadowMap()->BindFrameBuffer(); //Begin writing
//
//            m_directional_light_shadow_map_shader.SetDirectionalLight(dlight);
//
//            object.RenderAll(&m_directional_light_shadow_map_shader);
//
//        dlight->GetShadowMap()->UnBindFrameBuffer(); //stop writing
//
//    m_directional_light_shadow_map_shader.UnBind();
//}
//
void RenderingEngine::RenderEffects() {
    for (auto m_light : m_current_scene->getEffectEntities()) {
        StartBlendColor();
            m_light->RenderEffect(this);
        EndBlendColor();
    }
}

void RenderingEngine::RenderAllMeshed(){
    for (auto m_meshed : m_current_scene->getMeshedEntities()) {

        m_shaders[m_current_shader]->UpdateView(m_camera);

        m_shaders[m_current_shader]->UpdateProjection(m_projection);

        m_meshed->RenderAll(m_shaders[m_current_shader]);
    }
}

void RenderingEngine::RenderLights()
{
    for (auto m_light : m_current_scene->getLights()) {
        StartBlendColor();
            m_light->RenderLight(this);
        EndBlendColor();
    }
}

void RenderingEngine::RenderScene() {
    m_window->ResetViewPort();

    m_renderProfileTimer.StartInvocation();

        skybox.Draw(m_camera, m_projection);

        RenderAmbientLight();
        RenderLights();
        RenderEffects();

    m_renderProfileTimer.StopInvocation();
}

void RenderingEngine::ProcessInput(Input* input,float delta){
    m_camera.handleMouse(input->getXChange(),input->getYChange());
    m_camera.handleKeys(input->getKeys(),delta);
//    spotLights[0].SetAsFlashLight(m_camera);
}


Shader* RenderingEngine::GetShader(ShaderType type) {
    return m_shaders[type];
}

void RenderingEngine::SetCurrentShader(ShaderType type) {
    m_current_shader = type;
}

void RenderingEngine::SetCurrentScene(Scene * scene) {
    m_current_scene = scene;
}

