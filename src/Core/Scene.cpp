//
// Created by erick on 9/10/18.
//

#include "Scene.h"
#include "Game.h"
#include "CoreEngine.h"
#include "Entities/GUIEntity.h"

Scene::Scene(Game* game) : m_game(game){}

void Scene::Init() {}

void Scene::ProcessInput(Input* input, float delta) {
    for(MeshedEntity* m_meshed_Entity: m_meshed_Entities){
        m_meshed_Entity->ProcessInputAll(input,delta);
    }
    if(m_current_camera != nullptr) m_current_camera->ProcessInput(input,delta);
    if(m_current_mouse != nullptr) m_current_mouse->ProcessInput(input,delta);
}

void Scene::Update(double time, float delta) {
    for(LightEntity* m_light: m_lights){
        m_light->Update(time, delta);
    }

    for(MeshedEntity* m_meshed_Entity: m_meshed_Entities){
        m_meshed_Entity->UpdateAll(time, delta);
    }

    for(AnimatedEntity* m_animated_Entity: m_animated_Entities){
        m_animated_Entity->UpdateAll(time, delta);
    }

    if(m_current_skybox != nullptr) m_current_skybox->Update(time,delta);

    for(Water* water: m_waters){
        water->UpdateAll(time, delta);
    }
}

void Scene::AddLightToScene(LightEntity* light) {
//    switch(light->getType()){
//        case DIRECTIONAL_LIGHT:
//            directionalLightsCount++;
//            light->setId(directionalLightsCount - 1);
//            break;
//
//        case POINT_LIGHT:
//            pointLightsCount++;
//            light->setId(pointLightsCount - 1);
//            break;
//
//        case SPOT_LIGHT:
//            spotLightsCount++;
//            light->setId(spotLightsCount - 1);
//            break;
//
//        case NUM_LIGHT_TYPES:break;
//        default: break;
//    }
    lightsCount++;
    light->setId(lightsCount - 1);

    m_lights.push_back(light);
}
void Scene::AddMeshedToScene(MeshedEntity* meshed) { m_meshed_Entities.push_back(meshed);}
void Scene::AddAnimatedToScene(AnimatedEntity* animated) { m_animated_Entities.push_back(animated);}
void Scene::AddEffectToScene(EffectEntity* effect) { m_effect_Entities.push_back(effect);}
void Scene::AddCamera(Camera *camera) { m_cameras.push_back(camera); }
void Scene::AddSkyBox(SkyBox *skyBox) { m_skyboxes.push_back(skyBox); }
void Scene::AddTerrain(Terrain *terrain) {
    m_meshed_Entities.push_back(terrain);
    m_terrains.push_back(terrain);
}
void Scene::AddWaterBody(Water *water) {
    m_meshed_Entities.push_back(water);
    m_waters.push_back(water);
}
void Scene::AddMousePicker(MousePicker *picker) { m_current_mouse = picker; }


Game *Scene::getGame() const {
    return m_game;
}

const std::vector<LightEntity *> &Scene::getLights() const {
    return m_lights;
}

const std::vector<MeshedEntity *> &Scene::getMeshedEntities() const {
    return m_meshed_Entities;
}

const std::vector<Entity* > &Scene::getEntities() const {
    return m_entities;
}

const std::vector<EffectEntity *> &Scene::getEffectEntities() const {
    return m_effect_Entities;
}

const std::vector<Terrain *> &Scene::getTerrains() const {
    return m_terrains;
}

Camera *Scene::getCurrentCamera() const {
    return m_current_camera;
}

SkyBox *Scene::getCurrentSkybox() {
    return m_current_skybox;
}

void Scene::SetCurrentCamera(int position) {
    m_current_camera = m_cameras[position];
}

void Scene::SetCurrentSkyBox(int position) {
    m_current_skybox = m_skyboxes[position];
}

void Scene::AddGUI(GUIEntity *gui) {
    m_guis.push_back(gui);
}

const std::vector<GUIEntity *> Scene::getGUIs() const {
    return m_guis;
}

GUIEntity *Scene::getCurrentGUI() {
    return m_current_gui;
}

void Scene::SetCurrentGUI(int position) {
    m_current_gui = m_guis[position];
}

void Scene::AddPhysicsObject(PhysicsObject *object) {
    m_physics_object.push_back(object);
}

std::vector<PhysicsObject *> &Scene::getPhysicsObjects() {
    return m_physics_object;
}

void Scene::AddAnimatedEntity(AnimatedEntity *object) {
    m_animated_Entities.push_back(object);
}

const std::vector<AnimatedEntity *> &Scene::getAnimatedEntities() const {
    return m_animated_Entities;
}

const std::vector<Water *> &Scene::getWaterBodies() const {
    return m_waters;
}

void Scene::AddEntity(Entity *entity) {
    m_entities.push_back(entity);
}

int Scene::getSpotLightsCount() {
    return spotLightsCount;
}

int Scene::getPointLightsCount() {
    return pointLightsCount;
}

int Scene::getDirectionalLightsCount() {
    return directionalLightsCount;
}
