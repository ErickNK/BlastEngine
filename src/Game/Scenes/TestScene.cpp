//
// Created by erick on 9/10/18.
//

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

void TestScene::Init() {
        //Create required objects;
    DirectionalLight* directionalLight = new DirectionalLight(
            glm::vec3(1.0f,1.0f,1.0f),
            glm::vec3(0.0f,-1.0,-1.0f),
            0.0f, 0.1f,
            2018, 2018,
            glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 1000.0f));

    directionalLight->AddComponent(new LightComponent());
    this->AddLightToScene(directionalLight);

    PointLight* pointLight = new PointLight(glm::vec3(0.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,2.0f),
                                0.0f, 0.9f,
                                1.0f,0.245f,0.134f,
                                1024,1024);
    pointLight->AddComponent(new LightComponent());
    this->AddLightToScene(pointLight);

    SpotLight* spotLight = new SpotLight(
                        glm::vec3(1.0f,0.0f,1.0f),/*Color*/
                        glm::vec3(0.0f,2.0f,2.0f),/*position*/
                        glm::vec3(0.0f,-1.0f,0.0f),/*direction*/
                        0.0f, 0.7f,/*Ambient/diffuse intensity*/
                        1.0f,0.4f,0.3f, /*attenuation*/
                        20.0f, /*angle*/
                        1024, 1024);
    spotLight->AddComponent(new LightComponent());
    this->AddLightToScene(spotLight);

    auto * meshedLoader = new MeshedLoader();

    auto * nanosuit = new MeshedEntity();
    meshedLoader->LoadGameObject("../res/models/nanosuit/nanosuit.obj",nanosuit);
    this->AddMeshedToScene(nanosuit);

    std::map<TextureTypeEnum, std::string> textureLocations;
    textureLocations[DIFFUSE_TEXTURE] = "../res/textures/dirt.png";
    Terrain* terrain = new Terrain(0,0,textureLocations);
    this->AddMeshedToScene(terrain);

    Fog* fog = new Fog(glm::vec4(0.5,0.5,0.5,0.5),0.5f,0.5f);
    this->AddEffectToScene(fog);
}
