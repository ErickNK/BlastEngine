//
// Created by erick on 9/10/18.
//

#include "Scene.h"
#include "Game.h"
#include "CoreEngine.h"

Scene::Scene(Game* game) : m_game(game){}

void Scene::Init() {}

void Scene::ProcessInput(Input* input, float delta) {
    for(MeshedEntity* m_meshed_Entity: m_meshed_Entities){
        m_meshed_Entity->ProcessInputAll(input,delta);
    }
    m_current_camera->ProcessInput(input,delta);
}

void Scene::Update(float delta) {
    for(MeshedEntity* m_meshed_Entity: m_meshed_Entities){
        m_meshed_Entity->UpdateAll(delta);
    }
}

void Scene::AddLightToScene(LightEntity* light) { m_lights.push_back(light); }
void Scene::AddMeshedToScene(MeshedEntity* meshed) { m_meshed_Entities.push_back(meshed);}
void Scene::AddEffectToScene(EffectEntity* effect) { m_effect_Entities.push_back(effect);}
void Scene::AddCamera(Camera *camera) { m_cameras.push_back(camera); }
void Scene::AddSkyBox(SkyBox *skyBox) { m_skyboxes.push_back(skyBox); }
void Scene::AddTerrain(Terrain *terrain) {
    m_meshed_Entities.push_back(terrain);
    m_terrains.push_back(terrain);
}

Game *Scene::getGame() const {
    return m_game;
}

const std::vector<LightEntity *> &Scene::getLights() const {
    return m_lights;
}

const std::vector<MeshedEntity *> &Scene::getMeshedEntities() const {
    return m_meshed_Entities;
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