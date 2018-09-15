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
#include "../../Core/Entities/GUIEntity.h"
#include "../../Core/Components/RenderingComponents/GUIRendererComponent.h"
#include "../../Core/Components/RenderingComponents/ShadowRendererComponent.h"
#include "../../Core/Components/RenderingComponents/SkyBoxRendererComponent.h"

void TestScene::Init() {
    m_meshed_loader = new MeshedLoader();
    m_gui_loader = new GUILoader();
    SetupSkyBox();
    SetupCamera();
    CreateLighting();
    CreateTerrain();
    CreateCharacters();
    CreateGUI();
}

void TestScene::SetupSkyBox() {
    std::vector<std::string> faceLocations;

    faceLocations.emplace_back("../res/textures/skybox/cloudtop_lf.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_rt.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_up.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_dn.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_ft.tga");
    faceLocations.emplace_back("../res/textures/skybox/cloudtop_bk.tga");

    auto * skybox = new SkyBox(faceLocations);
    skybox->AddComponent(new SkyBoxRendererComponent());
    this->AddSkyBox(skybox);
    this->SetCurrentSkyBox(0);
}

void TestScene::SetupCamera(){
//    auto * tpsCamera = new TPSCamera(
//            glm::vec3(0.0f,10.0f,5.0f),
//            glm::vec3(0.0f,1.0f,0.0f),
//            0.0f,
//            0.0f,
//            0.0f,
//            15.0f,
//            0.005f
//    );

//    this->AddCamera(tpsCamera);

    auto * fpsCam = new FPSCamera(
            glm::vec3(0.0f,10.0f,5.0f),
            glm::vec3(0.0f,1.0f,0.0f),
            0.0f,
            0.0f,
            0.0f,
            15.0f,
            0.005f
    );
    fpsCam->setProjection(
            45.0f,
            (GLfloat)m_game->getCoreEngine()->GetWindow()->getBufferWidth() /
            (GLfloat)m_game->getCoreEngine()->GetWindow()->getBufferHeight(),
            1.0f,
            1000.0f
    );
    this->AddCamera(fpsCam);
    this->SetCurrentCamera(0);
}

void TestScene::CreateTerrain(){
    bool options[Num_Options];

    //Create Terrain
    std::map<TextureTypeEnum, std::string> terrainTextures;
    terrainTextures[BACKGROUND_TEXTURE] = "../res/textures/terrain/grassy2.png";
    terrainTextures[R_TEXTURE] = "../res/textures/terrain/mud.png";
    terrainTextures[G_TEXTURE] = "../res/textures/terrain/pinkFlowers.png";
    terrainTextures[B_TEXTURE] = "../res/textures/terrain/path.png";
    terrainTextures[BLEND_MAP_TEXTURE] = "../res/textures/terrain/blendMap.png";
    terrainTextures[HEIGHT_MAP_TEXTURE] = "../res/textures/terrain/heightmap.png";
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

        m_meshed_loader->LoadGameObject("../res/textures/terrain/tree.obj", treeTextures, tree, options);

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

        m_meshed_loader->LoadGameObject("../res/textures/terrain/grass.obj", grassTextures, grass, options);

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
        auto *fern = new MeshedEntity();

        std::mt19937 rng;
        rng.seed(std::random_device()());

        std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 4); // distribution in range [1, 100]

        std::map<TextureTypeEnum, std::string*> grassTextures;
        std::string atlasDetails[3] = {"../res/textures/terrain/fern.png",std::to_string(dist4(rng)),"2"};
        grassTextures[DIFFUSE_TEXTURE_ATLAS] = atlasDetails;

        options[Transparency] = true;
        options[FakeLighting] = true;

        m_meshed_loader->LoadGameObject("../res/textures/terrain/fern.obj", grassTextures, fern, options);

        std::uniform_int_distribution<std::mt19937::result_type> dist6(5, 500); // distribution in range [1, 100]

        fern->getTransform().GetPos().z = spice3 * dist6(rng);
        fern->getTransform().GetPos().x = spice3 * dist6(rng);

        this->AddMeshedToScene(fern);
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
            0.0f, 0.7f,
            2018, 2018,
            glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 1000.0f));

    directionalLight->AddComponent(new LightComponent());
    directionalLight->AddShadowComponent(new ShadowRendererComponent());
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

void TestScene::CreateGUI(){
    std::map<GUITexture*,Transform*> textures;
    GUITexture * healthTexture = new GUITexture("../res/textures/gui/health.png",GUI_TEXTURE);
    Transform* healthTransform = new Transform(glm::vec3(-0.75f,-0.9f,0.0f),glm::quat(),glm::vec3(0.25f,0.25f,0.25f));

    textures.emplace(healthTexture,healthTransform);

    auto * guiEntity = new GUIEntity();
    guiEntity->InitMesh();
    m_gui_loader->LoadGUI(textures,guiEntity);

    guiEntity->AddComponent(new GUIRendererComponent());

    this->AddGUI(guiEntity);
    this->SetCurrentGUI(0);
}