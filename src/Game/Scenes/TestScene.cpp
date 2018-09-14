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
#include "../../Core/Components/RenderingComponents/LightComponent.h"
#include "../../Core/Components/RenderingComponents/MeshedRendererComponent.h"
#include "../../Rendering/Loaders/MeshedLoader.h"
#include "../../Rendering/Fog.h"
#include "../../Core/Components/RenderingComponents/FogComponent.h"
#include "../../Rendering/Camera/FPSCamera.h"
#include "../../Core/Components/Behaviours/PlayerMovement.h"
#include "../../Rendering/Camera/TPSCamera.h"

void TestScene::Init() {
    m_meshed_loader = new MeshedLoader();

    SetupSkyBox();
    SetupCamera();
    CreateLighting();
    CreateTerrain();
    CreateCharacters();
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
    auto * tpsCamera = new TPSCamera(
            glm::vec3(0.0f,10.0f,5.0f),
            glm::vec3(0.0f,1.0f,0.0f),
            0.0f,
            0.0f,
            0.0f,
            15.0f,
            0.005f
    );

//    this->AddCamera(tpsCamera);

    this->AddCamera(new FPSCamera(
            glm::vec3(0.0f,10.0f,5.0f),
            glm::vec3(0.0f,1.0f,0.0f),
            0.0f,
            0.0f,
            0.0f,
            15.0f,
            0.005f
    ));
    this->SetCurrentCamera(0);
}

void  TestScene::CreateTerrain(){
    bool options[Num_Options];

    //Create Terrain
    std::map<TextureTypeEnum, std::string> terrainTextures;
    terrainTextures[BACKGROUND_TEXTURE] = "../res/textures/terrain/grassy2.png";
    terrainTextures[R_TEXTURE] = "../res/textures/terrain/mud.png";
    terrainTextures[G_TEXTURE] = "../res/textures/terrain/pinkFlowers.png";
    terrainTextures[B_TEXTURE] = "../res/textures/terrain/path.png";
    terrainTextures[BLEND_MAP_TEXTURE] = "../res/textures/terrain/blendMap.png";
    Terrain* terrain = new Terrain(0,0,terrainTextures);
    this->AddTerrain(terrain);

    Terrain* terrain1 = new Terrain(0,-1.0f,terrainTextures);
    this->AddTerrain(terrain1);

    Terrain* terrain2 = new Terrain(-1.0,0,terrainTextures);
    this->AddTerrain(terrain2);

    Terrain* terrain3 = new Terrain(-1.0,-1.0f,terrainTextures);
    this->AddTerrain(terrain3);

    //Trees
    int spice = 1;
    for(int i = 0; i < 50; i++) {
        auto *tree = new MeshedEntity();

        std::map<TextureTypeEnum, std::string> treeTextures;
        treeTextures[DIFFUSE_TEXTURE] = "../res/textures/terrain/tree.png";

        options[Transparency] = false;
        options[FakeLighting] = false;

        m_meshed_loader->LoadGameObjectWithTexture("../res/textures/terrain/tree.obj",treeTextures, tree, options);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(5, 500); // distribution in range [1, 100]

        tree->getTransform().GetPos().z = spice * dist6(rng);
        tree->getTransform().GetPos().x = spice * dist6(rng);
        tree->getTransform().SetScale(glm::vec3(10,10,10));

        this->AddMeshedToScene(tree);
        spice *= -1;
    }

    //grass
    int spice2 = 1;
    for(int i = 0; i < 80; i++) {
        auto *grass = new MeshedEntity();

        std::map<TextureTypeEnum, std::string> grassTextures;
        grassTextures[DIFFUSE_TEXTURE] = "../res/textures/terrain/grassTexture.png";

        options[Transparency] = true;
        options[FakeLighting] = true;

        m_meshed_loader->LoadGameObjectWithTexture("../res/textures/terrain/grass.obj",grassTextures, grass,options);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(5, 500); // distribution in range [1, 100]

        grass->getTransform().GetPos().z = spice2 * dist6(rng);
        grass->getTransform().GetPos().x = spice2 * dist6(rng);

        this->AddMeshedToScene(grass);
        spice2 *= -1;
    }

    //fern
    int spice3 = 1;
    for(int i = 0; i < 50; i++) {
        auto *grass = new MeshedEntity();

        std::map<TextureTypeEnum, std::string> grassTextures;
        grassTextures[DIFFUSE_TEXTURE] = "../res/textures/terrain/fern.png";

        options[Transparency] = true;
        options[FakeLighting] = true;

        m_meshed_loader->LoadGameObjectWithTexture("../res/textures/terrain/fern.obj",grassTextures, grass,options);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(5, 500); // distribution in range [1, 100]

        grass->getTransform().GetPos().z = spice3 * dist6(rng);
        grass->getTransform().GetPos().x = spice3 * dist6(rng);

        this->AddMeshedToScene(grass);
        spice3 *= -1;
    }

    Fog* fog = new Fog(glm::vec4(0.5,0.5,0.5,1.0),0.007f,2.5f);
    this->AddEffectToScene(fog);
}

void TestScene::CreateCharacters() {
    bool options[Num_Options];

    auto * nanosuit = new MeshedEntity();
    options[Transparency] = false;
    options[FakeLighting] = false;

    m_meshed_loader->LoadGameObject("../res/models/nanosuit/nanosuit.obj",nanosuit,options);
    auto * playMovement = new PlayerMovement();
    nanosuit->AddComponent(playMovement);
//
//    ((TPSCamera *)(this->getCurrentCamera()))->LookAt(nanosuit);
//    ((TPSCamera *)(this->getCurrentCamera()))->SetAttachmentComponent(new TPSCameraAttachment(nanosuit));
    this->AddMeshedToScene(nanosuit);

}

void TestScene::CreateLighting() {
    DirectionalLight* directionalLight = new DirectionalLight(
            glm::vec3(1.0f,1.0f,1.0f),
            glm::vec3(0.0f,-1.0,-1.0f),
            0.0f, 0.3f,
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

