//
// Created by erick on 9/10/18.
//

#ifndef MORDEROPENGLUDEMYTUTORIAL_TESTSCENE_H
#define MORDEROPENGLUDEMYTUTORIAL_TESTSCENE_H

#include "../../../src/Core/Scene.h"
#include "../../../src/Rendering/Loaders/MeshedLoader.h"
#include "../../../src/Rendering/Loaders/GUILoader.h"
#include "../../../src/Core/MousePicker.h"
#include "../../../src/Physics/Objects/RigidBody.h"

class TestScene : public Scene{
public:
    TestScene(Game* game): Scene(game){}

    void Init() override;

    void CreateLighting();

    void CreateCharacters();

    void CreateTerrain();

    void SetupCamera();

    void SetupSkyBox();

    void CreateGUI();

private:
    MeshedLoader * m_meshed_loader;
    GUILoader * m_gui_loader;
};


#endif //MORDEROPENGLUDEMYTUTORIAL_TESTSCENE_H
