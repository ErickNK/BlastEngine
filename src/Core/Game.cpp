//
// Created by erick on 9/7/18.
//

#include "Game.h"
#include "../Rendering/RenderingEngine.h"
#include "../Core/CoreEngine.h"

void Game::Init() {
    //Load required scene;

}

void Game::ProcessInput(Input* input, float delta)
{
    m_inputTimer.StartInvocation();
    m_currentScene->ProcessInput(input, delta);
    m_inputTimer.StopInvocation();
}

void Game::Update(float delta)
{
    m_updateTimer.StartInvocation();
    m_currentScene->Update(delta);
    m_updateTimer.StopInvocation();
}

void Game::Render()
{
    m_core_engine->GetRenderingEngine()->RenderScene();
}

CoreEngine *Game::getCoreEngine() const {
    return m_core_engine;
}

Scene* Game::getCurrentScene() const {
    return m_currentScene;
}

void Game::SetCurrentScene(Scene* scene) {
    m_core_engine->GetRenderingEngine()->SetCurrentScene(scene);
    m_currentScene = scene;
}
