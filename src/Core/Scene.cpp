//
// Created by erick on 9/10/18.
//

#include "Scene.h"
#include "Game.h"
#include "CoreEngine.h"

Scene::Scene(Game* game) : m_game(game){}

void Scene::Init() {}

void Scene::ProcessInput(const Input* input, float delta) {}

void Scene::Update(float delta) {}

void Scene::AddLightToScene(LightEntity* light) { m_lights.push_back(light); }
void Scene::AddMeshedToScene(MeshedEntity* meshed) { m_meshed_Entities.push_back(meshed);}
void Scene::AddEffectToScene(EffectEntity* effect) { m_effect_Entities.push_back(effect);}

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
