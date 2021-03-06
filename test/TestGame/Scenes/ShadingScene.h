//
// Created by erick on 9/26/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_SHADINGSCENE_H
#define MORDEROPENGLUDEMYTUTORIAL_SHADINGSCENE_H


#include "../../../src/Core/Scene.h"
#include "../../../src/Rendering/Loaders/MeshedLoader.h"
#include "../../../src/Rendering/Lighting/DirectionalLight.h"
#include "../../../src/Core/Components/RenderingComponents/LightComponent.h"
#include "../../../src/Core/Components/RenderingComponents/ShadowRendererComponent.h"
#include "../../../src/Core/Components/RenderingComponents/SkyBoxRendererComponent.h"
#include "../../../src/Core/Components/Behaviours/SkyBoxEffectsComponent.h"
#include "../../../src/Core/Components/RenderingComponents/GUIRendererComponent.h"
#include "../../../src/Rendering/Loaders/GUILoader.h"
#include "../components/SphereMovement.h"
#include "../../../src/Core/Components/Behaviours/PlayerMovement.h"
#include "../../../src/Rendering/Camera/TPSCamera.h"
#include "../../../src/Rendering/Loaders/AnimatedLoader.h"
#include "../../../src/Rendering/Loaders/AnimationLoader.h"

class ShadingScene : public Scene{
public:
    ShadingScene(Game* game): Scene(game){}

    void Init() override {
        m_meshed_loader = new MeshedLoader();
        m_animated_loader = new AnimatedLoader();
        m_animation_loader = new AnimationLoader();
        m_gui_loader = new GUILoader();
        SetupCamera();
        SetupLights();
        SetupObjects();
        CreateGUI();
    }

    void SetupCamera(){
        //CAMERA
        auto * camera = new TPSCamera(
                glm::vec3(0.0f,15.0f,10.0f),
                glm::vec3(0.0f,1.0f,0.0f),
                0.0f,
                0.0f,
                0.0f,
                15.0f,
                0.05f
        );
        camera->setProjection(
                45.0f,
                (GLfloat)m_game->getCoreEngine()->GetWindow()->getBufferWidth() /
                (GLfloat)m_game->getCoreEngine()->GetWindow()->getBufferHeight(),
                1.0f,
                1000.0f
        );
//        camera->setAllowMovement(false);
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

        ((TPSCamera*) this->getCurrentCamera())->SetAttachmentComponent(new TPSCameraAttachment(sphere));
        sphere->AddComponent(new PlayerMovement());

        sphere->getTransform().GetScale() *= 10.0f;
        sphere->getTransform().GetPos().y = 15.0f;
        this->AddMeshedToScene(sphere);
    }

    void SetupLights(){

        //LIGHT
        sun = new DirectionalLight(
                glm::vec3(1.0f,1.0f,1.0f),
                glm::vec3(15.0f,-15.0,0.0f),
                0.0f, 0.9f,
                2048, 2048,
                glm::ortho(-200.0f, 200.0f, -200.0f, 200.0f, 1.0f, 10000.0f));

        sun->getTransform().SetPos(glm::vec3(0.0f,100.0f,100.0f));
        sun->GetShadow().m_flipFaces = false;
        sun->AddComponent(new LightComponent());
//        sun->AddComponent(new LightMovement());
        sun->AddShadowComponent(new ShadowRendererComponent());
        this->AddLightToScene(sun);
    }

    void CreateGUI(){
        std::map<Texture*,Transform*> textures;

        textures.emplace(new Texture(sun->GetShadowMapFBO()->GetTextures()[sun->GetShadowMapTexture()],GUI_TEXTURE),new Transform(glm::vec3(0.5f,0.5f,0.0f),glm::quat(),glm::vec3(0.25f,0.25f,0.25f)));

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
    AnimatedLoader * m_animated_loader;
    AnimationLoader * m_animation_loader;
    GUILoader * m_gui_loader;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_SHADINGSCENE_H
