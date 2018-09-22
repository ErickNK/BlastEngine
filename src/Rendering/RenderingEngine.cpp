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
#include "Camera/Camera.h"
#include "SkyBox.h"
#include "Shaders/FogShader.h"
#include "Shaders/TerrainShader.h"
//TODO: avoid including entities in here
#include "../Core/Entities/GUIEntity.h"
#include "Shaders/GUIShader.h"
#include "Shaders/SkyBoxShader.h"
#include "Shaders/PostProcessingScreenShader.h"

RenderingEngine::RenderingEngine(Window* window): m_window(window) {
    CreateShaders();
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

    auto  * terrainShader = new TerrainShader();
    terrainShader->Init();
    m_shaders[TERRAIN_SHADER] = terrainShader;

    auto  * guiShader = new GUIShader();
    guiShader->Init();
    m_shaders[GUI_SHADER] = guiShader;

    auto  * skyboxShader = new SkyBoxShader();
    skyboxShader->Init();
    m_shaders[SKY_BOX_SHADER] = skyboxShader;

    auto  * postProcessingScreenShader = new PostProcessingScreenShader();
    postProcessingScreenShader->Init();
    m_shaders[POST_PROCESSING_SCREEN_SHADER] = postProcessingScreenShader;
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

void RenderingEngine::RenderEffects() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_ZERO,GL_SRC_COLOR);
//    glDepthMask(GL_FALSE);

        for (auto m_light : m_current_scene->getEffectEntities()) {
            m_light->Render(this);
        }

//    glDepthFunc(GL_LESS);
//    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void RenderingEngine::RenderAllMeshed(){
    for (auto m_meshed : m_current_scene->getMeshedEntities()) {

        m_shaders[m_current_shader]->UpdateCamera(*getCurrentScene()->getCurrentCamera());

        m_meshed->RenderAll(m_shaders[m_current_shader]);

        EnableCulling();
    }
}

void RenderingEngine::RenderLights()
{
    for (auto m_light : m_current_scene->getLights()) {
            m_light->RenderLight(this);
    }
}

void RenderingEngine::RenderTerrain() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_DST_COLOR,GL_ZERO);
    glBlendEquation(GL_ADD);
    glDepthMask(GL_FALSE);

    glDepthFunc(GL_EQUAL); //Do blend function on pixels that appear closest to the screen.
    for (auto m_Terrain : m_current_scene->getTerrains()) {
        m_Terrain->RenderTerrain(this);
    }

    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}

void RenderingEngine::RenderGUI() {
    StartAlphaBlending();
    glDisable(GL_DEPTH_TEST);
        auto * entity = m_current_scene->getCurrentGUI();
        if(entity != nullptr) entity->Render(this);
    glEnable(GL_DEPTH_TEST);
    EndAlphaBlending();
}

void RenderingEngine::RenderSkybox() {
    if(m_current_scene != nullptr) m_current_scene->getCurrentSkybox()->Render(this);
}

void RenderingEngine::RenderShadows() {
    for (auto m_light : m_current_scene->getLights()) {
        m_light->RenderShadow(this);
    }
}

void RenderingEngine::RenderScene() {
    this->EnableCulling();

    m_renderProfileTimer.StartInvocation();

//        RenderShadows();

        m_window->ResetViewPort();

        RenderSkybox();

        RenderAmbientLight();

        StartBlendColor();
            RenderLights();
        EndBlendColor();

        RenderTerrain();

        RenderEffects();

        RenderGUI();

    m_renderProfileTimer.StopInvocation();
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

Scene *RenderingEngine::getCurrentScene() const {
    return m_current_scene;
}

void RenderingEngine::EnableCulling() {
    //Enable Cull face
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void RenderingEngine::DisableCulling() {
    glDisable(GL_CULL_FACE);
}

void RenderingEngine::StartAlphaBlending() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void RenderingEngine::EndAlphaBlending() {
    glDisable(GL_BLEND);
}
