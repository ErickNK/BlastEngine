//
// Created by erick on 9/10/18.
//
#include <random>
#include <iostream>
#include "TestScene.h"
#include "../../../src/Rendering/Lighting/DirectionalLight.h"
#include "../../../src/Rendering/Lighting/PointLight.h"
#include "../../../src/Rendering/Lighting/SpotLight.h"
#include "../../../src/Rendering/Terrain/Terrain.h"
#include "../../../src/Core/Components/RenderingComponents/LightComponent.h"
#include "../../../src/Core/Components/RenderingComponents/MeshedRendererComponent.h"
#include "../../../src/Rendering/Loaders/MeshedLoader.h"
#include "../../../src/Rendering/Fog.h"
#include "../../../src/Core/Components/RenderingComponents/FogComponent.h"
#include "../../../src/Rendering/Camera/FPSCamera.h"
#include "../../../src/Core/Components/Behaviours/PlayerMovement.h"
#include "../../../src/Rendering/Camera/TPSCamera.h"
#include "../../../src/Core/Entities/GUIEntity.h"
#include "../../../src/Core/Components/RenderingComponents/GUIRendererComponent.h"
#include "../../../src/Core/Components/RenderingComponents/ShadowRendererComponent.h"
#include "../../../src/Core/Components/RenderingComponents/SkyBoxRendererComponent.h"
#include "../../../src/Core/Components/Behaviours/SkyBoxEffectsComponent.h"
#include "../../../src/Core/MousePicker.h"
#include "../../../src/Physics/Colliders/Point.h"
#include "../../../src/Physics/Colliders/TerrainCollider.h"
#include "../../../src/Physics/Objects/TerrainBody.h"
#include "../../../src/Core/Components/Behaviours/LightRotationComponent.h"
#include "../../../src/Rendering/Primitives/Water.h"
#include "../../../src/Rendering/PostProcessing/Screen.h"

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
    std::map<SkyBoxTypes, std::vector<std::string>> faceLocations;

    faceLocations[DAY_SKYBOX].emplace_back("../test/TestGame/res/textures/skybox/cloudtop_lf.tga");
    faceLocations[DAY_SKYBOX].emplace_back("../test/TestGame/res/textures/skybox/cloudtop_rt.tga");
    faceLocations[DAY_SKYBOX].emplace_back("../test/TestGame/res/textures/skybox/cloudtop_up.tga");
    faceLocations[DAY_SKYBOX].emplace_back("../test/TestGame/res/textures/skybox/cloudtop_dn.tga");
    faceLocations[DAY_SKYBOX].emplace_back("../test/TestGame/res/textures/skybox/cloudtop_ft.tga");
    faceLocations[DAY_SKYBOX].emplace_back("../test/TestGame/res/textures/skybox/cloudtop_bk.tga");

    faceLocations[NIGHT_SKYBOX].emplace_back("../test/TestGame/res/textures/skybox/night_lf.png");
    faceLocations[NIGHT_SKYBOX].emplace_back("../test/TestGame/res/textures/skybox/night_rt.png");
    faceLocations[NIGHT_SKYBOX].emplace_back("../test/TestGame/res/textures/skybox/night_up.png");
    faceLocations[NIGHT_SKYBOX].emplace_back("../test/TestGame/res/textures/skybox/night_dn.png");
    faceLocations[NIGHT_SKYBOX].emplace_back("../test/TestGame/res/textures/skybox/night_ft.png");
    faceLocations[NIGHT_SKYBOX].emplace_back("../test/TestGame/res/textures/skybox/night_bk.png");

    auto * skybox = new SkyBox(100.f,faceLocations);
    skybox->AddComponent(new SkyBoxRendererComponent())
    ->AddComponent(new SkyBoxEffectsComponent());

//    Fog* fog = new Fog(glm::vec4(0.2,0.2,0.2,1.0),0.007f,10.5f);
//    skybox->setFog(fog);
//    skybox->setFogUpperLimit(70.0f);
//    this->AddEffectToScene(fog);

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

    auto * fpsCam = new Camera(
            glm::vec3(0.0f,15.0f,-5.0f),
            glm::vec3(0.0f,1.0f,0.0f),
//            0.0f,
            0.0f,
            0.0f,
            15.0f,
            0.5f
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

//    auto * mousePicker = new MousePicker(this->getCurrentCamera(),this->getGame()->getCoreEngine()->GetWindow());
//    this->AddMousePicker(mousePicker);

}

void TestScene::CreateTerrain(){
    bool options[Num_Options];

    //Create Terrain
    std::map<TextureTypeEnum, std::string> terrainTextures;
    terrainTextures[BACKGROUND_TEXTURE] = "../test/TestGame/res/textures/terrain/grassy2.png";
    terrainTextures[R_TEXTURE] = "../test/TestGame/res/textures/terrain/mud.png";
    terrainTextures[G_TEXTURE] = "../test/TestGame/res/textures/terrain/pinkFlowers.png";
    terrainTextures[B_TEXTURE] = "../test/TestGame/res/textures/terrain/path.png";
    terrainTextures[BLEND_MAP_TEXTURE] = "../test/TestGame/res/textures/terrain/blendMap.png";
    terrainTextures[HEIGHT_MAP_TEXTURE] = "../test/TestGame/res/textures/terrain/heightmap.png";

    Terrain* terrain = new Terrain(0,0,terrainTextures);
    auto * terrainBody = new TerrainBody();
    terrain->AddComponent(reinterpret_cast<EntityComponent<MeshedEntity> *>(terrainBody));
    this->AddPhysicsObject(terrainBody);
    this->AddTerrain(terrain);

//    std::map<TextureTypeEnum, std::string> waterTextures;
//    waterTextures[DU_DV_MAP] = "../test/TestGame/res/textures/terrain/waterDUDV.png";
//    waterTextures[NORMAL_MAP] = "../test/TestGame/res/textures/terrain/matchingNormalMap.png";
//    auto * water = new Water(1,1,-5,waterTextures);
//    this->AddWaterBody(water);

    //Trees
    int spice = 1;
    for(int i = 0; i < 50; i++) {
        auto *tree = new MeshedEntity();

        std::map<TextureTypeEnum, std::string> treeTextures;
        treeTextures[DIFFUSE_TEXTURE] = "../test/TestGame/res/textures/terrain/tree.png";

        options[Transparency] = false;
        options[FakeLighting] = false;

        m_meshed_loader->LoadGameObject("../test/TestGame/res/textures/terrain/tree.obj", treeTextures, tree, options);

        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(5, 500); // distribution in range [1, 100]

        tree->getTransform().GetPos().z = spice * dist6(rng);
        tree->getTransform().GetPos().x = spice * dist6(rng);
        tree->getTransform().SetScale(glm::vec3(10,10,10));

        auto * rigidBody = new RigidBody(new Point(),glm::vec3(0,0,0),100.0f);
        tree->AddComponent(reinterpret_cast<EntityComponent<MeshedEntity> *>(rigidBody));
        this->AddPhysicsObject(rigidBody);
        this->AddMeshedToScene(tree);
        spice *= -1;
    }

    //fern
    int spice3 = 1;
    for(int i = 0; i < 50; i++) {
        auto *fern = new MeshedEntity();

        std::mt19937 rng;
        rng.seed(std::random_device()());

        std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 4); // distribution in range [1, 100]

        std::map<TextureTypeEnum, std::string*> grassTextures;
        std::string atlasDetails[3] = {"../test/TestGame/res/textures/terrain/fern.png",std::to_string(dist4(rng)),"2"};
        grassTextures[DIFFUSE_TEXTURE_ATLAS] = atlasDetails;

        options[Transparency] = true;
        options[FakeLighting] = true;

        m_meshed_loader->LoadGameObject("../test/TestGame/res/textures/terrain/fern.obj", grassTextures, fern, options);

        std::uniform_int_distribution<std::mt19937::result_type> dist6(5, 500); // distribution in range [1, 100]

        fern->getTransform().GetPos().z = spice3 * dist6(rng);
        fern->getTransform().GetPos().x = spice3 * dist6(rng);

        auto * rigidBody = new RigidBody(new Point(),glm::vec3(0,0,0),100.0f);
        fern->AddComponent(reinterpret_cast<EntityComponent<MeshedEntity> *>(rigidBody));
        this->AddPhysicsObject(rigidBody);
        this->AddMeshedToScene(fern);
        spice3 *= -1;
    }
}

void TestScene::CreateCharacters() {
    bool options[Num_Options];

    auto * nanosuit = new MeshedEntity();
    options[Transparency] = false;
    options[FakeLighting] = false;

    m_meshed_loader->LoadGameObject("../test/TestGame/res/models/nanosuit/nanosuit.obj",nanosuit,options);

    auto * rigidBody = new RigidBody(new Point(),glm::vec3(0,0,0),100.0f);
    nanosuit->AddComponent(reinterpret_cast<EntityComponent<MeshedEntity> *>(rigidBody));
//            ->AddComponent(new PlayerMovement());

//    ((TPSCamera*) this->getCurrentCamera())->SetAttachmentComponent(new TPSCameraAttachment(nanosuit));
    this->AddPhysicsObject(rigidBody);
    this->AddMeshedToScene(nanosuit);
}

void TestScene::CreateLighting() {
    sun = new DirectionalLight(
            glm::vec3(1.0f,1.0f,1.0f),
            glm::vec3(0.0f,-1.0,1.0f),
            0.0f, 0.9f,
            2018, 2018,
            glm::ortho(-200.0f, 200.0f, -200.0f, 200.0f, 1.0f, 10000.0f));

    sun->getTransform().SetPos(glm::vec3(0.0f,100.0f,0.0f));
    sun->getTransform().LookAt(glm::vec3(0.0f,-1.0,1.0f));
    sun->GetShadow().m_flipFaces = false;
    sun->AddComponent(new LightComponent());
    sun->AddShadowComponent(new ShadowRendererComponent());
    this->AddLightToScene(sun);

//    PointLight* pointLight = new PointLight(
//            glm::vec3(0.0f,1.0f,1.0f), /*Color*/
//            glm::vec3(-2.0f,2.0f,2.0f), /*Position*/
//            0.0f, 1.0f, /*Ambient/diffuse*/
//            glm::vec3(0.1002f,0.1209f,1.0f), /*Attenuation*/
//            1024,1024); /*Shadow*/
//    pointLight->AddComponent(new LightComponent())
//    ->AddComponent(new LightRotationComponent());
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
    std::map<Texture*,Transform*> textures;

//    textures.emplace(this->m_waters[0]->getReflectionFBO().GetTexture(this->m_waters[0]->getReflectionTexture()),new Transform(glm::vec3(-0.5f,0.5f,0.0f),glm::quat(),glm::vec3(0.25f,0.25f,0.25f)));
//    textures.emplace(this->m_waters[0]->getRefractionFBO().GetTexture(this->m_waters[0]->getRefractionTexture()),new Transform(glm::vec3(0.5f,0.5f,0.0f),glm::quat(),glm::vec3(0.25f,0.25f,0.25f)));
//    textures.emplace(new Texture("../res/textures/gui/health.png",GUI_TEXTURE),new Transform(glm::vec3(-0.75f,-0.9f,0.0f),glm::quat(),glm::vec3(0.25f,0.25f,0.25f)));
    textures.emplace(new Texture(sun->GetShadowMapFBO().GetTextures()[sun->GetShadowMapTexture()],GUI_TEXTURE),new Transform(glm::vec3(0.5f,0.5f,0.0f),glm::quat(),glm::vec3(0.25f,0.25f,0.25f)));

    auto * guiEntity = new GUIEntity();
    guiEntity->InitMesh();
    m_gui_loader->LoadGUI(textures,guiEntity);

    guiEntity->AddComponent(new GUIRendererComponent());

    this->AddGUI(guiEntity);
    this->SetCurrentGUI(0);
}