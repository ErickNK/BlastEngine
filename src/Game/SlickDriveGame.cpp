//
// Created by erick on 9/8/18.
//

#include "SlickDriveGame.h"
#include "../Rendering/Lighting/DirectionalLight.h"
#include "../Rendering/Lighting/PointLight.h"
#include "../Rendering/Lighting/SpotLight.h"
#include "../Rendering/Terrain/Terrain.h"

void SlickDriveGame::Init(const Window* window) {

    DirectionalLight* directionalLight = new DirectionalLight(
            glm::vec3(1.0f,1.0f,1.0f),
            glm::vec3(0.0f,-1.0,-1.0f),
            0.0f, 0.1f,
            2018, 2018,
            glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 1000.0f));

    getRootObject().AddComponent(directionalLight);

    PointLight* pointLight = new PointLight(glm::vec3(0.0f,1.0f,1.0f),glm::vec3(0.0f,5.0f,2.0f),
                                0.0f, 0.9f,
                                1.0f,0.245f,0.134f,
                                1024,1024);
    getRootObject().AddComponent(pointLight);

    SpotLight* spotLight = new SpotLight(
                                       glm::vec3(1.0f,0.0f,1.0f),/*Color*/
                                       glm::vec3(0.0f,2.0f,2.0f),/*position*/
                                       glm::vec3(0.0f,-1.0f,0.0f),/*direction*/
                                       0.0f, 0.7f,/*Ambient/diffuse intensity*/
                                       1.0f,0.4f,0.3f, /*attenuation*/
                                       20.0f, /*angle*/
                                       1024, 1024);
    getRootObject().AddComponent(spotLight);

    auto * nanosuit = new GameObject("../res/models/nanosuit/nanosuit.obj");
    if(nanosuit->LoadGameObject()) getRootObject().AddChild(nanosuit);
//
//    auto * house = new GameObject("../res/models/Cartoon Land/Free Cartoon Land 2.obj");
//    house->getMaterial().setShininess(5.0f);
//    house->getMaterial().setSpecularIntensity(0.2f);
//    if(house->LoadGameObject()) getRootObject().AddChild(house);

    std::map<TextureTypeEnum, std::string> textureLocations;
    textureLocations[DIFFUSE_TEXTURE] = "../res/textures/dirt.png";

    Terrain* terrain = new Terrain(0,0,textureLocations);
    getRootObject().AddChild(terrain);

    Terrain* terrain1 = new Terrain(-1,0,textureLocations);
    getRootObject().AddChild(terrain1);

    Terrain* terrain2 = new Terrain(0,-1,textureLocations);
    getRootObject().AddChild(terrain2);

    Terrain* terrain3 = new Terrain(-1,-1,textureLocations);
    getRootObject().AddChild(terrain3);

};