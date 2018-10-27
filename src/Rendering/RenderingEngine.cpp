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
#include <fmt/format.h>

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
#include "Shaders/WaterShader.h"
#include "Shaders/DifferedShader.h"
#include "../Core/Components/RenderingComponents/DifferedRenderingComponent.h"
#include "../Core/Exceptions/ShaderException.h"
#include "../Core/Exceptions/RenderingEngineException.h"

void RenderingEngine::Initialize(){

    //Setup Shaders
    CreateShaders();
    m_current_shader.push(NO_SHADER);

    //Setup FBOs
    PushFBO(new FrameBufferObject(0,m_window->getBufferWidth(),m_window->getBufferHeight()));

    //Setup Rendering Components
    int id = static_cast<int>(m_renderingComponents.size());
    m_renderingComponents[id] = new DifferedRenderingComponent(id,this);
    m_current_renderingComponents_ids.push_back(id);

    //Setup clip planes
    for (bool &m_activated_clipping_Plane : m_activated_clipping_Planes) {
        m_activated_clipping_Plane = false;
    }

    //Setup flags
    for (bool& flag : m_flags) {
        flag = false;
    }

    //Check errors
    glCheckError();
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

    auto  * waterShader = new WaterShader();
    waterShader->Init();
    m_shaders[WATER_SHADER] = waterShader;

    auto  * differedGeometryPassShader = new DifferedGeometryPassShader();
    differedGeometryPassShader->Init();
    m_shaders[DIFFERED_GEOMETRYPASS_RENDERING_SHADER] = differedGeometryPassShader;

    auto  * differedLightPassShader = new DifferedLightPassShader();
    differedLightPassShader->Init();
    m_shaders[DIFFERED_LIGHTPASS_RENDERING_SHADER] = differedLightPassShader;

    auto  * differedShadowPassShader = new DifferedShadowPassShader();
    differedShadowPassShader->Init();
    m_shaders[DIFFERED_SHADOWPASS_RENDERING_SHADER] = differedShadowPassShader;
}

void RenderingEngine::RenderAmbientLight(){
    auto * ambient_light_shader = (ForwardAmbientShader*)  BindShader(FORWARD_AMBIENT_SHADER);

        ambient_light_shader->setLight(glm::vec3(1,1,1),0.3f);

        RenderAllMeshed();

    UnBindShader(FORWARD_AMBIENT_SHADER);
}

void RenderingEngine::RenderEffects() {
    if(m_flags[RENDER_EFFECTS]) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
        glDepthMask(GL_FALSE);

        for (auto m_light : m_current_scene->getEffectEntities()) {
            m_light->Render(this);
        }

        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
    }
}

void RenderingEngine::RenderAllMeshed(){
    for (auto m_meshed : m_current_scene->getMeshedEntities()) {

        m_meshed->RenderAll(this);

        EnableCulling();
    }

    for (auto m_meshed : m_current_scene->getAnimatedEntities()) {

        m_meshed->RenderAll(this);

        EnableCulling();
    }
}

void RenderingEngine::RenderLights()
{
    if(m_flags[RENDER_LIGHTS]) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_EQUAL); //Do blend function on pixels that appear closest to the screen.

        for (auto m_light : m_current_scene->getLights()) {
            m_light->RenderLight(this);
        }

        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);

        glCheckError();

    }
}

void RenderingEngine::RenderTerrain() {
    if(m_flags[RENDER_TERRAIN]) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_DST_COLOR, GL_ZERO);
        glBlendEquation(GL_FUNC_ADD);
        glDepthMask(GL_FALSE);
        glDepthFunc(GL_EQUAL); //Do blend function on pixels that appear closest to the screen.

        for (auto m_Terrain : m_current_scene->getTerrains()) {
            m_Terrain->RenderTerrain(this);
        }

        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);

        glCheckError();

    }
}

void RenderingEngine::RenderGUI() {
    if(m_flags[RENDER_GUI]) {
        StartAlphaBlending();
        glDisable(GL_DEPTH_TEST);
        auto *entity = m_current_scene->getCurrentGUI();
        if (entity != nullptr) entity->Render(this);
        glEnable(GL_DEPTH_TEST);
        EndAlphaBlending();

        glCheckError();

    }
}

void RenderingEngine::RenderSkybox() {
    if(m_flags[RENDER_SKYBOX]){
        if(m_current_scene != nullptr && m_current_scene->getCurrentSkybox() != nullptr)
            m_current_scene->getCurrentSkybox()->Render(this);
    }

    glCheckError();

}

void RenderingEngine::RenderShadows() {
    if(m_flags[RENDER_SHADOW]){
        for (auto m_light : m_current_scene->getLights()) {
            m_light->RenderShadow(this);
        }

        glCheckError();

    }
}

void RenderingEngine::RenderWater(){
    if(m_flags[RENDER_WATER]) {
        for (auto m_water : m_current_scene->getWaterBodies()) {
            m_water->RenderWater(this);
        }

        glCheckError();

    }
}

void RenderingEngine::RenderScene() {
    this->EnableCulling();

    if(!m_current_renderingComponents_ids.empty()){
        m_renderingComponents[m_current_renderingComponents_ids.back()]->RenderScene();
    }else{
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR, 0,
                             GL_DEBUG_SEVERITY_HIGH, -1, "No Rendering Component bound!.");
        throw RenderingEngineException(fmt::format(R"(Type: "No Rendering Component bound!.")"));
    }

    glCheckError();
}

Shader* RenderingEngine::BindShader(ShaderType type) {
    //Replace previous
    m_current_shader.top() = type;

    return BindShader();
}

Shader *RenderingEngine::BindShader() {
    if(!m_current_shader.empty()) { //If not empty
        if(m_current_shader.top() != NO_SHADER) { //If its not the base shader
            //Bind for use
            m_shaders[m_current_shader.top()]->Bind();

            //Update the shader
            UpdateShader(m_shaders[m_current_shader.top()]);

            return m_shaders[m_current_shader.top()];
        }else{
            glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR, 0,
                                 GL_DEBUG_SEVERITY_HIGH, -1, "No shader bound!.");
            throw RenderingEngineException(fmt::format(R"(Type: "No shader bound!.")"));
        }
    }else{
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR, 0,
                             GL_DEBUG_SEVERITY_HIGH, -1, "No shader bound!.");
        throw RenderingEngineException(fmt::format(R"(Type: "No shader bound!.")"));
    }
}

void RenderingEngine::UnBindShader(ShaderType type) {
    //UnBind for use
    m_shaders[type]->UnBind();
}

Shader *RenderingEngine::PushShader(ShaderType type) {
    if(m_current_shader.top() != NO_SHADER) { //If its not the base shader

        //UnBind previous
        m_shaders[m_current_shader.top()]->UnBind();

    }
    //New shader
    m_current_shader.push(type);

    return BindShader();
}

void RenderingEngine::PopShader() {
    //UnBind previous
    m_shaders[m_current_shader.top()]->UnBind();

    //Back to previous
    m_current_shader.pop();

    BindShader();
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

Shader* RenderingEngine::UpdateShader(Shader *shader) {
    //Update View
    shader->UpdateCamera(*getCurrentScene()->getCurrentCamera());

    //Update clipping planes
    for(int i = 0; i < MAX_CLIP_PLANES; i++){
        if(m_activated_clipping_Planes[i]) shader->ActivateClipPlane(i,m_clipping_Planes[i]);
        else shader->DeactivateClipPlane(i);
    }

}

void RenderingEngine::ActivateClipPlane(int id, glm::vec4& plane) {
    m_activated_clipping_Planes[id] = true;
    m_clipping_Planes[id] = plane;
}

void RenderingEngine::DeactivateClipPlane(int id) {
    m_activated_clipping_Planes[id] = false;
}

void RenderingEngine::CleanUP() {

}

Window *RenderingEngine::getWindow() {
    return m_window;
}

Shader *RenderingEngine::getShader(ShaderType type) {
    return m_shaders[type];
}

ShaderType RenderingEngine::getCurrentShaderType() {
    return m_current_shader.top();
}

void RenderingEngine::setWindow(Window *window) {
    m_window = window;
}

void RenderingEngine::BindFBO() {
    if(!m_current_fbos.empty()) {

        glBindFramebuffer(GL_FRAMEBUFFER, m_current_fbos.back()->GetFrameBuffer()); //Bind shadow buffer.

        glViewport(0, 0, m_current_fbos.back()->GetWidth(), m_current_fbos.back()->GetHeight());

    }else{
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR, 0,
                             GL_DEBUG_SEVERITY_HIGH, -1, "No FrameBuffer bound!.");
        throw RenderingEngineException(fmt::format(R"(Type: "No FrameBuffer bound!.")"));
    }
}

void RenderingEngine::ReplaceTopFBO(FrameBufferObject* fbo) {

    m_current_fbos.back() = fbo;

    BindFBO();
}

void RenderingEngine::ResetTopToOriginalFBO() {

    m_current_fbos.back() = new FrameBufferObject(0,m_window->getBufferWidth(),m_window->getBufferHeight());

    BindFBO();
}

void RenderingEngine::PopFBO() {

    m_current_fbos.pop_back();

    BindFBO();
}

void RenderingEngine::PushFBO(FrameBufferObject* fbo) {
    if(std::find(m_current_fbos.begin(), m_current_fbos.end(), fbo) == m_current_fbos.end()){ //Not found

        m_current_fbos.push_back(fbo);

        BindFBO();

    }else{ //FBO is already in use
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR, 0,
                             GL_DEBUG_SEVERITY_HIGH, -1, "FrameBuffer already in use. Cannot override existing data!");
        throw RenderingEngineException(fmt::format(R"(Type: "FrameBuffer already in use. Cannot override existing data!")"));
    }
}

void RenderingEngine::PushRenderingComponent(int id) {
    m_current_renderingComponents_ids.push_back(id);
}

void RenderingEngine::PopRenderingComponent() {
    m_current_renderingComponents_ids.pop_back();
}

void RenderingEngine::RequestRenderingComponent(int &id) {
    id = static_cast<int>(m_renderingComponents.size());
    m_renderingComponents[id] = new DifferedRenderingComponent(id,this);
}

int RenderingEngine::RequestRenderingComponent() {
    int id = static_cast<int>(m_renderingComponents.size());
    m_renderingComponents[id] = new DifferedRenderingComponent(id,this);

    return id;
}

void RenderingEngine::DeactivateAllClipPlanes() {
    //Setup clip planes
    for(int i = 0; i < MAX_CLIP_PLANES; i++){
        glDisable(GL_CLIP_DISTANCE0 + i);
    }

    glCheckError();

}

const bool RenderingEngine::getFlag(RenderEngineFlags type) const {
    return m_flags[type];
}

const bool *RenderingEngine::getFlags() const {
    return m_flags;
}

void RenderingEngine::setFlag(RenderEngineFlags type, bool value) {
    m_flags[type] = value;
}


