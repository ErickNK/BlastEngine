//
// Created by erick on 9/10/18.
//
#include <random>
#include <iostream>
#include "TestScene.h"
#include "../../Rendering/Lighting/DirectionalLight.h"
#include "../../Rendering/Lighting/PointLight.h"
#include "../../Rendering/Lighting/SpotLight.h"
#include "../../Rendering/Terrain/Terrain.h"
#include "../../Core/Components/LightComponent.h"
#include "../../Core/Components/MeshedRendererComponent.h"
#include "../../Rendering/Loaders/MeshedLoader.h"
#include "../../Rendering/Fog.h"
#include "../../Core/Components/FogComponent.h"
#include "../../Rendering/Camera/FPSCamera.h"

void TestScene::Init() {
    m_meshed_loader = new MeshedLoader();

    SetupSkyBox();
    SetupCamera();
    CreateLighting();
    CreateCharacters();
    CreateTerrain();
}

void TestScene::SetupSkyBox() {
    std::vector<std::string> faceLocations;

    faceLocations.emplace_back("../res/textures/skybox/cloudtop_lf.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_rt.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_up.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_dn.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_ft.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_bk.tga");

    this->AddSkyBox(new SkyBox(faceLocations));
    this->SetCurrentSkyBox(0);
}

void TestScene::SetupCamera(){
    this->AddCamera(
        new Camera(
            glm::vec3(2.0f,2.0f,5.0f),
            glm::vec3(0.0f,1.0f,0.0f),
            -90.0f,
            0.0f,
            15.0f,
            0.5f
        )
    );
    this->SetCurrentCamera(0);
}

void  TestScene::CreateTerrain(){
    //Create Terrain
    std::map<TextureTypeEnum, std::string> textureLocations;
    textureLocations[DIFFUSE_TEXTURE] = "../res/textures/terrain/grass.png";
    Terrain* terrain = new Terrain(0,0,textureLocations);
    this->AddMeshedToScene(terrain);

    Terrain* terrain1 = new Terrain(0,-1.0f,textureLocations);
    this->AddMeshedToScene(terrain1);

    Terrain* terrain2 = new Terrain(-1.0,0,textureLocations);
    this->AddMeshedToScene(terrain2);

    Terrain* terrain3 = new Terrain(-1.0,-1.0f,textureLocations);
    this->AddMeshedToScene(terrain3);

    //Trees
    int spice = 1;
    for(int i = 0; i < 100; i++) {
        auto *tree = new MeshedEntity();
        m_meshed_loader->LoadGameObject("../res/textures/terrain/tree.obj", tree);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(5, 1000); // distribution in range [1, 100]

        tree->getTransform().GetPos().z = spice * dist6(rng);
        tree->getTransform().GetPos().x = spice * dist6(rng);
        tree->getTransform().SetScale(glm::vec3(10,10,10));

        this->AddMeshedToScene(tree);
        spice *= -1;
    }

    //Grass

    Fog* fog = new Fog(glm::vec4(0.2,0.2,0.2,1.0),0.007f,2.5f);
    this->AddEffectToScene(fog);
}

void TestScene::CreateCharacters() {

    auto * nanosuit = new MeshedEntity();
    m_meshed_loader->LoadGameObject("../res/models/nanosuit/nanosuit.obj",nanosuit);
    nanosuit->getTransform().GetPos().z = 5.0f;
    nanosuit->getTransform().GetPos().x = 5.0f;
    this->AddMeshedToScene(nanosuit);

}

void TestScene::CreateLighting() {
    DirectionalLight* directionalLight = new DirectionalLight(
            glm::vec3(1.0f,1.0f,1.0f),
            glm::vec3(0.0f,-1.0,-1.0f),
            0.0f, 0.1f,
            2018, 2018,
            glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 1000.0f));

    directionalLight->AddComponent(new LightComponent());
    this->AddLightToScene(directionalLight);

//    PointLight* pointLight = new PointLight(
//            glm::vec3(0.0f,1.0f,1.0f), /*Color*/
//            glm::vec3(-2.0f,2.0f,2.0f), /*Position*/
//            0.0f, 1.0f, /*Ambient/diffuse*/
//            glm::vec3(0.134f,0.245f,1.0f), /*Attenuation*/
//            1024,1024); /*Shadow*/
//    pointLight->AddComponent(new LightComponent());
//    this->AddLightToScene(pointLight);

//    SpotLight* spotLight = new SpotLight(
//            glm::vec3(1.0f,0.0f,1.0f),/*Color*/
//            glm::vec3(10.0f,10.0f,10.0f),/*position*/
//            glm::vec3(0.0f,-1.0f,1.0f),/*direction*/
//            0.0f, 0.7f,/*Ambient/diffuse intensity*/
//            glm::vec3(0.0f,0.0f,1.0f), /*attenuation*/
//            20.0f, /*angle*/
//            1024, 1024);
//    spotLight->AddComponent(new LightComponent());
//    this->AddLightToScene(spotLight);
}

