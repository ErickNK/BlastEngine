//
// Created by erick on 9/8/18.
//

#include "SlickDriveGame.h"
#include "../Rendering/Lighting/DirectionalLight.h"
#include "../Rendering/Lighting/PointLight.h"
#include "../Rendering/Lighting/SpotLight.h"
#include "../Rendering/Terrain/Terrain.h"
#include "Scenes/TestScene.h"
#include "Scenes/ShadingScene.h"

void SlickDriveGame::Init() {

    auto * scene = new ShadingScene(this);
    scene->Init();
    this->SetCurrentScene(scene);
};