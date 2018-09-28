//
// Created by erick on 9/26/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SHADINGSCENE_H
#define MORDEROPENGLUDEMYTUTORIAL_SHADINGSCENE_H


#include "../../Core/Scene.h"
#include "../../Rendering/Loaders/MeshedLoader.h"
#include "../../Rendering/Lighting/DirectionalLight.h"
#include "../../Core/Components/RenderingComponents/LightComponent.h"
#include "../../Core/Components/RenderingComponents/ShadowRendererComponent.h"
#include "../../Core/Components/RenderingComponents/SkyBoxRendererComponent.h"
#include "../../Core/Components/Behaviours/SkyBoxEffectsComponent.h"
#include "../../Core/Components/RenderingComponents/GUIRendererComponent.h"
#include "../../Rendering/Loaders/GUILoader.h"
#include "../SphereMovement.h"

class ShadingScene : public Scene{
public:
    ShadingScene(Game* game): Scene(game){}

    void Init() override {
        m_meshed_loader = new MeshedLoader();
        m_gui_loader = new GUILoader();
        SetupCamera();
        SetupLights();
        SetupObjects();
        CreateGUI();
    }

    void SetupCamera(){
        //CAMERA
        auto * camera = new QuatCamera(
                glm::vec3(0.0f,15.0f,10.0f),
                glm::vec3(0.0f,1.0f,0.0f),
                0.0f,
                0.0f,
                15.0f,
                0.0005f
        );
        camera->setProjection(
                45.0f,
                (GLfloat)m_game->getCoreEngine()->GetWindow()->getBufferWidth() /
                (GLfloat)m_game->getCoreEngine()->GetWindow()->getBufferHeight(),
                1.0f,
                1000.0f
        );
        this->AddCamera(camera);
        this->SetCurrentCamera(0);
    }

    void SetupObjects(){
        //PLANE
        bool options[Num_Options];

        auto * plane = new MeshedEntity();
        options[Transparency] = false;
        options[FakeLighting] = false;

        m_meshed_loader->LoadGameObject("../res/objects/plane_bottom.obj",plane,options);
        plane->getTransform().GetScale() *= 200.0f;
        this->AddMeshedToScene(plane);

        //SPHERE
        auto * sphere = new MeshedEntity();
        options[Transparency] = false;
        options[FakeLighting] = false;

        m_meshed_loader->LoadGameObject("../res/objects/sphere.obj",sphere,options);
        sphere->getTransform().GetScale() *= 10.0f;
        sphere->getTransform().GetPos().y = 15.0f;
        this->AddMeshedToScene(sphere);
    }

    void SetupLights(){

        //LIGHT
        sun = new DirectionalLight(
                glm::vec3(1.0f,1.0f,1.0f),
                glm::vec3(0.0f,-1.0,-1.0f),
                0.0f, 0.9f,
                2048, 2048,
                glm::ortho(-200.0f, 200.0f, -200.0f, 200.0f, 1.0f, 10000.0f));

        sun->AddComponent(new LightComponent());
        sun->AddComponent(new LightMovement());
        sun->AddShadowComponent(new ShadowRendererComponent());
        this->AddLightToScene(sun);
    }

    void CreateGUI(){
        std::map<Texture*,Transform*> textures;

//    textures.emplace(this->m_waters[0]->getReflectionFBO().GetTexture(this->m_waters[0]->getReflectionTexture()),new Transform(glm::vec3(-0.5f,0.5f,0.0f),glm::quat(),glm::vec3(0.25f,0.25f,0.25f)));
    textures.emplace(new Texture(sun->GetShadowMapFBO().GetTextures()[sun->GetShadowMapTexture()],GUI_TEXTURE),new Transform(glm::vec3(0.5f,0.5f,0.0f),glm::quat(),glm::vec3(0.25f,0.25f,0.25f)));
//    textures.emplace(new Texture("../res/textures/gui/health.png",GUI_TEXTURE),new Transform(glm::vec3(-0.75f,-0.9f,0.0f),glm::quat(),glm::vec3(0.25f,0.25f,0.25f)));

        auto * guiEntity = new GUIEntity();
        guiEntity->InitMesh();
        m_gui_loader->LoadGUI(textures,guiEntity);

        guiEntity->AddComponent(new GUIRendererComponent());

        this->AddGUI(guiEntity);
        this->SetCurrentGUI(0);
    }

private:
    DirectionalLight* sun;
    MeshedLoader * m_meshed_loader;
    GUILoader * m_gui_loader;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_SHADINGSCENE_H
