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

RenderingEngine::RenderingEngine(Window* window): m_window(window) {
    CreateShaders();
    SetupPerspective();
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

        ambient_light_shader->setLight(glm::vec3(1,1,1),0.006);

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
            m_light->RenderEffect(this);
    }
}

void RenderingEngine::RenderAllMeshed(){
    for (auto m_meshed : m_current_scene->getMeshedEntities()) {

        m_shaders[m_current_shader]->UpdateView(*m_camera);

        m_shaders[m_current_shader]->UpdateProjection(m_projection);

        m_meshed->RenderAll(m_shaders[m_current_shader]);
    }
}

void RenderingEngine::RenderLights()
{
    for (auto m_light : m_current_scene->getLights()) {
            m_light->RenderLight(this);
    }
}

void RenderingEngine::RenderTerrain() {
    for (auto m_Terrain : m_current_scene->getTerrains()) {
        m_Terrain->RenderTerrain(this);
    }
}

void RenderingEngine::RenderGUI() {
    auto * entity = m_current_scene->getCurrentGUI();
    if(entity != nullptr) entity->RenderGUI(this);
}


void RenderingEngine::RenderScene() {
    this->EnableCulling();

    m_camera = m_current_scene->getCurrentCamera();

    m_window->ResetViewPort();

    m_renderProfileTimer.StartInvocation();

        m_current_scene->getCurrentSkybox()->Draw(*m_camera, m_projection);

        RenderAmbientLight();

        StartBlendColor();

            RenderLights();
            RenderEffects();
            RenderTerrain();

        EndBlendColor();

        StartAlphaBlending();
        glDisable(GL_DEPTH_TEST);
            RenderGUI();
        glEnable(GL_DEPTH_TEST);
        EndAlphaBlending();

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

const glm::mat4 &RenderingEngine::getProjection() const {
    return m_projection;
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
